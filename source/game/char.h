// find:
		int				GetSyncHackCount() { return m_iSyncHackCount; }

// paste below:
#ifdef ENABLE_RESP_SYSTEM
	public:
		LPREGEN	GetRegen() { return m_pkRegen; }
		PIXEL_POSITION GetRegenPos() { return m_posRegen; }

		bool	CanActRespManager() { return g_setRespAllowedMap.find(GetMapIndex()) != g_setRespAllowedMap.end(); }
#endif
