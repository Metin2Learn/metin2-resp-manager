// find:
#include "desc_client.h"

// paste below:
#ifdef ENABLE_RESP_SYSTEM
#include "resp_manager.h"
#endif

// find:
	DSManager dsManager;

// paste below:
#ifdef ENABLE_RESP_SYSTEM
	CRespManager resp_manager;
#endif
