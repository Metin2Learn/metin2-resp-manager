// find:
#include "DragonSoul.h"

// paste below:
#ifdef ENABLE_RESP_SYSTEM
#include "resp_manager.h"
#endif

// find:
	sys_log(0, "DISCONNECT: %s (%s)", GetName(), c_pszReason ? c_pszReason : "unset" );

// paste below:
#ifdef ENABLE_RESP_SYSTEM
	CRespManager::instance().LogoutFromMap(this);
#endif

// find:
	m_posRegen = GetXYZ();

// paste below:
#ifdef ENABLE_RESP_SYSTEM
	CRespManager::instance().RegisterMob(this);
#endif
