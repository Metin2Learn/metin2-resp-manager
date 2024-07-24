// find:
bool ITEM_MANAGER::CreateDropItem(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<LPITEM> & vec_item)
{
    [...]
}

// paste below:
#if defined(ENABLE_DROP_INFO) | defined(ENABLE_RESP_SYSTEM)
bool ITEM_MANAGER::CreateDropItemInfo(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<TDropInfoItem>& vec_item)
{
	int iLevel = pkKiller->GetLevel();

	int iDeltaPercent, iRandRange;
	if (!GetDropPct(pkChr, pkKiller, iDeltaPercent, iRandRange))
		return false;

	BYTE bRank = pkChr->GetMobRank();
	DWORD dwMobVnum = pkChr->GetRaceNum();

	// hit cache
	if (m_map_pkDropInfoCache.find(dwMobVnum) != m_map_pkDropInfoCache.end())
	{
		vec_item = m_map_pkDropInfoCache[dwMobVnum];
		return vec_item.size();
	}

	std::map<DWORD, TDropInfoItem> map_item;

	// Common Drop Items
	for (const auto& it : g_vec_pkCommonDropItem[bRank])
	{
		if (iLevel < it.m_iLevelStart || iLevel > it.m_iLevelEnd)
			continue;

		TDropInfoItem item{ it.m_dwVnum, 1 };
		
		if (map_item.find(it.m_dwVnum) == map_item.end())
			map_item[it.m_dwVnum] = item;
	}

	// Drop Item Group
	{
		const auto find = m_map_pkDropItemGroup.find(dwMobVnum);
		if (find != m_map_pkDropItemGroup.end())
		{
			for (const auto& it : find->second->GetVector())
			{
				TDropInfoItem item{ it.dwVnum, static_cast<BYTE>(it.iCount) };

				if (map_item.find(it.dwVnum) == map_item.end())
				{
					map_item[it.dwVnum] = item;
				}
				else
				{
					const auto tab = &map_item[it.dwVnum];
					tab->byMaxCount += item.byMinCount;
					if (item.byMinCount < tab->byMinCount)
						tab->byMinCount = item.byMinCount;
				}
			}
		}
	}

	// MobDropItem Group
	{
		const auto find = m_map_pkMobItemGroup.find(dwMobVnum);
		if (find != m_map_pkMobItemGroup.end())
		{
			for (const auto& it : find->second->GetVector())
			{
				TDropInfoItem item{ it.dwItemVnum, static_cast<BYTE>(it.iCount) };
				
				if (map_item.find(it.dwItemVnum) == map_item.end())
				{
					map_item[it.dwItemVnum] = item;
				}
				else
				{
					const auto tab = &map_item[it.dwItemVnum];
					tab->byMaxCount += item.byMinCount;
					if (item.byMinCount < tab->byMinCount)
						tab->byMinCount = item.byMinCount;
				}
			}
		}
	}	
	
	// Level Item Group
	{
		const auto find = m_map_pkLevelItemGroup.find(dwMobVnum);
		if (find != m_map_pkLevelItemGroup.end())
		{
			for (const auto& it : find->second->GetVector())
			{
				TDropInfoItem item{ it.dwVNum, static_cast<BYTE>(it.iCount) };
				
				if (map_item.find(it.dwVNum) == map_item.end())
				{
					map_item[it.dwVNum] = item;
				}
				else
				{
					const auto tab = &map_item[it.dwVNum];
					tab->byMaxCount += item.byMinCount;
					if (item.byMinCount < tab->byMinCount)
						tab->byMinCount = item.byMinCount;
				}
			}
		}
	}
	// Level Item Group
	{
		if (pkKiller->GetPremiumRemainSeconds(PREMIUM_ITEM) > 0 ||
			pkKiller->IsEquipUniqueGroup(UNIQUE_GROUP_DOUBLE_ITEM))
		{
			const auto find = m_map_pkGloveItemGroup.find(dwMobVnum);
			if (find != m_map_pkGloveItemGroup.end())
			{
				for (const auto& it : find->second->GetVector())
				{
					TDropInfoItem item{ it.dwVnum, static_cast<BYTE>(it.iCount) };
					
					if (map_item.find(it.dwVnum) == map_item.end())
					{
						map_item[it.dwVnum] = item;
					}
					else
					{
						const auto tab = &map_item[it.dwVnum];
						tab->byMaxCount += item.byMinCount;
						if (item.byMinCount < tab->byMinCount)
							tab->byMinCount = item.byMinCount;
					}
				}
			}
		}
	}

	if (pkChr->GetMobDropItemVnum())
	{
		const auto it = m_map_dwEtcItemDropProb.find(pkChr->GetMobDropItemVnum());

		if (it != m_map_dwEtcItemDropProb.end())
		{
			TDropInfoItem item{ pkChr->GetMobDropItemVnum(), 1 };
			
			if (map_item.find(pkChr->GetMobDropItemVnum()) == map_item.end())
				map_item[pkChr->GetMobDropItemVnum()] = item;
		}
	}

	if (pkChr->IsStone() && pkChr->GetDropMetinStoneVnum())
	{
		TDropInfoItem item{ pkChr->GetDropMetinStoneVnum(), 1 };
		
		if (map_item.find(pkChr->GetDropMetinStoneVnum()) == map_item.end())
			map_item[pkChr->GetDropMetinStoneVnum()] = item;
	}

	std::transform(map_item.begin(), map_item.end(), std::back_inserter(vec_item), [&](auto& kv) { return kv.second; });

	//CreateQuestDropItem(pkChr, pkKiller, vec_item, iDeltaPercent, iRandRange);

	// save cache
	m_map_pkDropInfoCache[dwMobVnum] = vec_item;

	return vec_item.size();
}
#endif