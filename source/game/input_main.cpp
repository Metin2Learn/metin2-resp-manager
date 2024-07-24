// find:
#include "DragonSoul.h"

// paste below:
#ifdef ENABLE_RESP_SYSTEM
#include "resp_manager.h"
#endif

// find:
		case HEADER_CG_DRAGON_SOUL_REFINE:
			{
				[...]
			}
			break;

// paste below:
#ifdef ENABLE_RESP_SYSTEM
		case HEADER_CG_RESP:
			if ((iExtraLen = Resp(ch, c_pData, m_iBufferLeft)) < 0)
				return -1;
			break;
#endif

// add at the end of the file:
#ifdef ENABLE_RESP_SYSTEM
int CInputMain::Resp(LPCHARACTER ch, const char* c_pData, size_t uiBytes)
{
	if (!ch || !ch->GetDesc())
		return -1;

	TPacketCGRespHeader* p = (TPacketCGRespHeader*)c_pData;

	if (uiBytes < sizeof(TPacketCGRespHeader))
		return -1;

	c_pData += sizeof(TPacketCGRespHeader);
	uiBytes -= sizeof(TPacketCGRespHeader);

	switch (p->subheader)
	{
		case RESP_CG_SUBHEADER_FETCH_RESP:
		case RESP_CG_SUBHEADER_FETCH_DROP:
		{
			if (uiBytes < sizeof(uint32_t))
				return -1;

			uint32_t mobVnum = *(uint32_t*)c_pData;
			c_pData += sizeof(uint32_t);
			uiBytes -= sizeof(uint32_t);

			if (ch->CanActRespManager())
				CRespManager::instance().FetchData(ch, p->subheader, mobVnum);

			return sizeof(uint32_t);
		}

		case RESP_CG_SUBHEADER_TELEPORT:
		{
			if (uiBytes < sizeof(size_t))
				return -1;

			size_t id = *(size_t*)c_pData;
			c_pData += sizeof(size_t);
			uiBytes -= sizeof(size_t);

			if (ch->CanActRespManager())
				CRespManager::instance().Teleport(ch, id);

			return sizeof(size_t);
		}

		default:
			sys_err("Unknown subheader %d", p->subheader);
			return -1;
	}
}
#endif
