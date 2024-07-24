// find:
#include "dungeon.h"

// paste below:
#ifdef ENABLE_RESP_SYSTEM
#include "resp_manager.h"
size_t m_regenId = 0;
#endif

// find:
				str_to_number(regen->vnum, szTmp);

// paste below:
#ifdef ENABLE_RESP_SYSTEM
				regen->id = m_regenId++;
#endif
