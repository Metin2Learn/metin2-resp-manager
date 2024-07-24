// find:
long FN_get_apply_type(const char *apply_type_string)
{
	[...]
}

// paste below:
#ifdef ENABLE_RESP_SYSTEM
std::set<uint32_t> g_setRespAllowedMap = {
	1, 3, 21, 23, 41, 43, 61, 62, 63, 64, 65, 68, 71, 72, 104
};
#endif
