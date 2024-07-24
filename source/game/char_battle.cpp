// find:
#include "DragonLair.h"

// paste below:
#ifdef ENABLE_RESP_SYSTEM
#include "resp_manager.h"
#endif

// find:
	if (IsPC())
	{
		m_dwLastDeadTime = get_dword_time();
		SetKillerMode(false);
		GetDesc()->SetPhase(PHASE_DEAD);
	}
	else
	{
		[...]
	}

// paste below (https://filipdev.com/wp-content/uploads/2023/04/Screenshot_21.png :
	if (IsPC())
	{
		m_dwLastDeadTime = get_dword_time();
		SetKillerMode(false);
		GetDesc()->SetPhase(PHASE_DEAD);
	}
	else
	{
#ifdef ENABLE_RESP_SYSTEM
		CRespManager::instance().KillMob(this);
#endif
		[...]
	}
