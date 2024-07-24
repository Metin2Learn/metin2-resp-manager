// find:
#include "MarkManager.h"

// paste below:
#ifdef ENABLE_RESP_SYSTEM
#include "resp_manager.h"
#endif

// find:
	if (g_noticeBattleZone)
	{
		[...]
	}

// paste below:
#ifdef ENABLE_RESP_SYSTEM
	CRespManager::instance().LoginToMap(ch);
#endif
