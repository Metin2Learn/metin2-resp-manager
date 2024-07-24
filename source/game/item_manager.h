// find:
		const SMobItemGroupInfo& GetOne() const
		{
			return m_vecItems[GetOneIndex()];
		}

// paste below:
#if defined(ENABLE_DROP_INFO) | defined(ENABLE_RESP_SYSTEM)
		std::vector<SMobItemGroupInfo> GetVector() const
		{
			return m_vecItems;
		}
#endif

// find:
class CBuyerThiefGlovesItemGroup
{
    [...]
}

// paste below:
#if defined(ENABLE_DROP_INFO) | defined(ENABLE_RESP_SYSTEM)
typedef struct SDropInfoItem
{
	DWORD	dwVnum;
	BYTE	byMinCount;
	BYTE	byMaxCount;

	SDropInfoItem()
	{
		dwVnum = 0;
		byMinCount = 0;
		byMaxCount = 0;
	}

	SDropInfoItem(DWORD vnum, BYTE count)
	{
		dwVnum = vnum;
		byMinCount = count;
		byMaxCount = count;
	}
	
	bool operator<(const struct SDropInfoItem& rhs) const
	{
		return dwVnum < rhs.dwVnum;
	}

} TDropInfoItem;
#endif

// find:
		bool ReadItemVnumMaskTable(const char * c_pszFileName);

// paste below:
#if defined(ENABLE_DROP_INFO) | defined(ENABLE_RESP_SYSTEM)
		bool			CreateDropItemInfo(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<TDropInfoItem>& vec_item);
		void			ClearDropInfoCache() { m_map_pkDropInfoCache.clear(); }
		std::map<DWORD, std::vector<TDropInfoItem>>		m_map_pkDropInfoCache;
#endif
