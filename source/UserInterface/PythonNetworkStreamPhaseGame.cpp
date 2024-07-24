// find:
			case HEADER_GC_DRAGON_SOUL_REFINE:
				ret = RecvDragonSoulRefine();
				break;

// paste below:
#ifdef ENABLE_RESP_SYSTEM
			case HEADER_GC_RESP:
				ret = RecvRespPacket();
				break;
#endif

// add at the end of the file:
#ifdef ENABLE_RESP_SYSTEM
bool CPythonNetworkStream::SendRespFetchDropPacket(uint32_t mobVnum)
{
	if (!__CanActMainInstance())
		return false;

	TPacketCGRespHeader header{};
	header.header = HEADER_CG_RESP;
	header.subheader = RESP_CG_SUBHEADER_FETCH_DROP;

	if (!Send(sizeof(TPacketCGRespHeader), &header) ||
		!Send(sizeof(uint32_t), &mobVnum))
		return false;

	return SendSequence();
}

bool CPythonNetworkStream::SendRespFetchRespPacket(uint32_t mobVnum)
{
	if (!__CanActMainInstance())
		return false;

	TPacketCGRespHeader header{};
	header.header = HEADER_CG_RESP;
	header.subheader = RESP_CG_SUBHEADER_FETCH_RESP;

	if (!Send(sizeof(TPacketCGRespHeader), &header) ||
		!Send(sizeof(uint32_t), &mobVnum))
		return false;

	return SendSequence();
}

bool CPythonNetworkStream::SendRespTeleportPacket(size_t id)
{
	if (!__CanActMainInstance())
		return false;

	TPacketCGRespHeader header{};
	header.header = HEADER_CG_RESP;
	header.subheader = RESP_CG_SUBHEADER_TELEPORT;

	if (!Send(sizeof(TPacketCGRespHeader), &header) ||
		!Send(sizeof(size_t), &id))
		return false;

	return SendSequence();
}

bool CPythonNetworkStream::RecvRespPacket()
{
	TPacketGCRespHeader header{};
	if (!Recv(sizeof(TPacketGCRespHeader), &header))
		return false;

	switch (header.subheader)
	{
		case RESP_GC_SUBHEADER_DATA_RESP:
		case RESP_GC_SUBHEADER_DATA_DROP:
		{
			uint16_t itemCount = 0;
			if (!Recv(sizeof(uint16_t), &itemCount))
				return false;

			uint32_t mobVnum = 0;
			if (!Recv(sizeof(uint32_t), &mobVnum))
				return false;

			switch (header.subheader)
			{
				case RESP_GC_SUBHEADER_DATA_RESP:
				{
					PyObject* respDataList = PyList_New(itemCount);

					for (int i=0; i < itemCount; i++)
					{
						TPacketGCRespData pack{};
						if (!Recv(sizeof(TPacketGCRespData), &pack))
							return false;

						PyObject* positionTuple = PyTuple_New(2);
						PyTuple_SetItem(positionTuple, 0, Py_BuildValue("i", pack.x));
						PyTuple_SetItem(positionTuple, 1, Py_BuildValue("i", pack.y));

						PyObject* respDict = PyDict_New();

						PyDict_SetItem(respDict, Py_BuildValue("s", "resp"), Py_BuildValue("i", pack.nextRespTime));
						PyDict_SetItem(respDict, Py_BuildValue("s", "cord"), Py_BuildValue("O", positionTuple));
						PyDict_SetItem(respDict, Py_BuildValue("s", "time"), Py_BuildValue("i", pack.time));
						PyDict_SetItem(respDict, Py_BuildValue("s", "id"), Py_BuildValue("k", pack.id));

						PyList_SetItem(respDataList, i, respDict);
					}

					PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_SetMobRespData", Py_BuildValue("(lO)", mobVnum, respDataList));

					break;
				}

				case RESP_GC_SUBHEADER_DATA_DROP:
				{
					TPacketGCRespGold gold{};
					if (!Recv(sizeof(TPacketGCRespGold), &gold))
						return false;

					PyObject* dropDataList = PyList_New(itemCount + 1);

					PyObject* goldDropDict = PyDict_New();

					PyDict_SetItem(goldDropDict, Py_BuildValue("s", "vnum"), Py_BuildValue("i", 1));
					PyDict_SetItem(goldDropDict, Py_BuildValue("s", "count"), Py_BuildValue("i", gold.minGold));

					PyList_SetItem(dropDataList, 0, goldDropDict);

					for (int i = 0; i < itemCount; i++)
					{
						TPacketGCRespItem data{};
						if (!Recv(sizeof(TPacketGCRespItem), &data))
							return false;

						PyObject* dropDict = PyDict_New();

						PyDict_SetItem(dropDict, Py_BuildValue("s", "vnum"), Py_BuildValue("i", data.vnum));
						PyDict_SetItem(dropDict, Py_BuildValue("s", "count"), Py_BuildValue("i", data.minCount));

						PyList_SetItem(dropDataList, i + 1, dropDict);
					}

					PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_SetMobDropData", Py_BuildValue("(lO)", mobVnum, dropDataList));

					break;
				}
			}
			break;
		}
		case RESP_GC_SUBHEADER_DATA_MOB:
		{
			TPacketGCMapData pack{};
			if (!Recv(sizeof(TPacketGCMapData), &pack))
				return false;

			PyObject* mobDataList = PyList_New(pack.mobCount);

			for (int i = 0; i < pack.mobCount; i++)
			{
				uint32_t mobVnum = 0;
				if (!Recv(sizeof(uint32_t), &mobVnum))
					return false;

				PyList_SetItem(mobDataList, i, Py_BuildValue("l", mobVnum));
			}

			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_SetMapData", Py_BuildValue("(Oiiii)", 
				mobDataList, pack.currentBossCount, pack.maxBossCount, pack.currentMetinCount, pack.maxMetinCount));
			break;
		}
		case RESP_GC_SUBHEADER_REFRESH_RESP:
		{
			TPacketGCRespRefresh pack{};
			if (!Recv(sizeof(TPacketGCRespRefresh), &pack))
				return false;

			PyObject* positionTuple = PyTuple_New(2);
			PyTuple_SetItem(positionTuple, 0, Py_BuildValue("i", pack.x));
			PyTuple_SetItem(positionTuple, 1, Py_BuildValue("i", pack.y));

			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_RefreshResp", Py_BuildValue("(klLO)", pack.id, pack.vnum, pack.nextRespTime, positionTuple));

			break;
		}
	}

	return true;
}
#endif
