// find:
#ifdef ENABLE_NEW_EQUIPMENT_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_NEW_EQUIPMENT_SYSTEM",	1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_NEW_EQUIPMENT_SYSTEM",	0);
#endif

// paste below:
#ifdef ENABLE_RESP_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_RESP_SYSTEM", true);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_RESP_SYSTEM", false);
#endif
