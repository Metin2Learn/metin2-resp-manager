// find:
		void __BettingGuildWar_SetBettingMoney(UINT uBettingMoney);

// paste below:
#ifdef ENABLE_RESP_SYSTEM
	public:
		bool SendRespFetchDropPacket(uint32_t mobVnum);
		bool SendRespFetchRespPacket(uint32_t mobVnum);
		bool SendRespTeleportPacket(size_t id);
	private:
		bool RecvRespPacket();
#endif
