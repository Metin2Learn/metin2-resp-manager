// search for:
	Set(HEADER_CG_STATE_CHECKER, sizeof(BYTE), "ServerStateCheck", false);

// add under:
#ifdef ENABLE_RESP_SYSTEM
	Set(HEADER_CG_RESP, sizeof(SPacketCGRespHeader), "Resp", true);
#endif
