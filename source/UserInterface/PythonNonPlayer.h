// find:
		enum EMobResists
		{
			[...]
		};

// paste below:
#if defined (ENABLE_ELEMENT_ADD) || defined(ENABLE_DROP_INFO) || defined(ENABLE_RESP_SYSTEM)
		enum ERaceFlags
		{
			RACE_FLAG_ANIMAL = (1 << 0),
			RACE_FLAG_UNDEAD = (1 << 1),
			RACE_FLAG_DEVIL = (1 << 2),
			RACE_FLAG_HUMAN = (1 << 3),
			RACE_FLAG_ORC = (1 << 4),
			RACE_FLAG_MILGYO = (1 << 5),
			RACE_FLAG_INSECT = (1 << 6),
			RACE_FLAG_FIRE = (1 << 7),
			RACE_FLAG_ICE = (1 << 8),
			RACE_FLAG_DESERT = (1 << 9),
			RACE_FLAG_TREE = (1 << 10),
			RACE_FLAG_ATT_ELEC = (1 << 11),
			RACE_FLAG_ATT_FIRE = (1 << 12),
			RACE_FLAG_ATT_ICE = (1 << 13),
			RACE_FLAG_ATT_WIND = (1 << 14),
			RACE_FLAG_ATT_EARTH = (1 << 15),
			RACE_FLAG_ATT_DARK = (1 << 16),
		};

		enum EImmuneFlags
		{
			IMMUNE_STUN = (1 << 0),
			IMMUNE_SLOW = (1 << 1),
			IMMUNE_FALL = (1 << 2),
			IMMUNE_CURSE = (1 << 3),
			IMMUNE_POISON = (1 << 4),
			IMMUNE_TERROR = (1 << 5),
			IMMUNE_REFLECT = (1 << 6),
		};
#endif


// find:
		const char*			GetMonsterName(DWORD dwVnum);

// paste below:
#if defined(ENABLE_TELEPORT_SYSTEM) || defined(ENABLE_RESP_SYSTEM)
		BYTE				GetMonsterLevel(DWORD dwVnum);
#endif
