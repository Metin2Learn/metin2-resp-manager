// find:
			Set(HEADER_GC_DRAGON_SOUL_REFINE,		CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDragonSoulRefine), STATIC_SIZE_PACKET));

// paste below:
#ifdef ENABLE_RESP_SYSTEM
			Set(HEADER_GC_RESP, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCRespHeader), DYNAMIC_SIZE_PACKET));
#endif
