#include "stdafx.h"

#ifdef ENABLE_RESP_SYSTEM
#include "char.h"
#include "regen.h"
#include "packet.h"
#include "buffer_manager.h"
#include "item_manager.h"
#include "mob_manager.h"
#include "desc.h"
#include "wedding.h"
#include "OXEvent.h"
#include "resp_manager.h"

CRespMapData::CRespMapData()
{
}

CRespMapData::~CRespMapData()
{
	m_setCharacter.clear();
	m_mapRespData.clear();
	m_mapMob.clear();
}

void CRespMapData::LoginToMap(const LPCHARACTER ch)
{
	if (m_setCharacter.find(ch) == m_setCharacter.end())
		m_setCharacter.insert(ch);
}

void CRespMapData::LogoutFromMap(const LPCHARACTER ch)
{
	if (m_setCharacter.find(ch) != m_setCharacter.end())
		m_setCharacter.erase(ch);
}

bool CRespMapData::RegisterMob(const size_t id, const uint32_t vnum, const bool is_stone, const uint32_t x, const uint32_t y, const uint32_t time)
{	
	if (m_mapMob.find(vnum) == m_mapMob.end())
		m_mapMob.emplace(vnum, is_stone);

	const auto& it = m_mapRespData.find(id);
	if (it == m_mapRespData.end())
	{
		std::shared_ptr<CRespData> respData = std::make_shared<CRespData>(vnum, x, y, time);
		m_mapRespData.insert(std::make_pair(id, respData));

		return false;
	}

	const auto& respData = it->second;

	respData->x = x;
	respData->y = y;
	respData->time = time;

	return true;
}

time_t CRespMapData::KillMob(const uint32_t id)
{
	const auto& it = m_mapRespData.find(id);

	if (it == m_mapRespData.end())
		return 0;

	const auto& respData = it->second;

	respData->nextRespTime = respData->time + time(nullptr);

	return respData->nextRespTime;
}

bool CRespMapData::HasMob(uint32_t mobVnum)
{
	return std::any_of(m_mapRespData.begin(), m_mapRespData.end(),
		[mobVnum](const auto& it) 
		{ 
			return it.second->vnum == mobVnum; 
		}
	);
}

std::shared_ptr<CRespData> CRespMapData::GetRespData(size_t id)
{
	const auto& it = m_mapRespData.find(id);
	if (it != m_mapRespData.end())
		return it->second;

	return nullptr;
}

CRespManager::CRespManager()
{

}

CRespManager::~CRespManager()
{
	m_mapMapData.clear();
}

std::shared_ptr<CRespMapData> CRespManager::RegisterMap(const uint32_t mapIndex)
{
	if (m_mapMapData.find(mapIndex) != m_mapMapData.end())
		return nullptr;

	std::shared_ptr<CRespMapData> mapData = std::make_shared<CRespMapData>();
	m_mapMapData.emplace(mapIndex, mapData);

	sys_log(0, "RESP_MANAGER: map %d registered", mapIndex);

	return mapData;
}

std::shared_ptr<CRespMapData> CRespManager::GetMap(const uint32_t mapIndex)
{
	const auto& it = m_mapMapData.find(mapIndex);

	if (it == m_mapMapData.end())
		return nullptr;

	return it->second;
}

void CRespManager::LoginToMap(const LPCHARACTER ch)
{
	const auto& mapData = GetMap(ch->GetMapIndex());
	if (!mapData)
		return;

	mapData->LoginToMap(ch);

	if (ch->GetDesc())
	{
		const auto& mapMob = mapData->GetMapMob();
		uint8_t mobCount = static_cast<uint8_t>(mapMob.size());

		const auto& respData = mapData->GetRespData();
		const auto& now = time(nullptr);

		TEMP_BUFFER buf;

		TPacketGCRespHeader header{};
		header.header = HEADER_GC_RESP;
		header.size = sizeof(TPacketGCRespHeader) + sizeof(TPacketGCMapData) + sizeof(uint32_t) * mobCount;
		header.subheader = RESP_GC_SUBHEADER_DATA_MOB;

		TPacketGCMapData pack{};
		pack.mobCount = mobCount;

		for (const auto& it : respData)
		{
			const auto& data = it.second;
			const auto& isStone = mapMob.at(data->vnum);

			if (isStone)
			{
				pack.maxMetinCount++;
				if (data->nextRespTime <= now)
					pack.currentMetinCount++;
			}
			else
			{
				pack.maxBossCount++;
				if (data->nextRespTime <= now)
					pack.currentBossCount++;
			}
		}

		buf.write(&header, sizeof(TPacketGCRespHeader));
		buf.write(&pack, sizeof(TPacketGCMapData));
		for (const auto& it : mapMob)
			buf.write(&it.first, sizeof(uint32_t));

		ch->GetDesc()->Packet(buf.read_peek(), buf.size());
	}

	sys_log(0, "RESP_MANAGER: player %s login to map %d", ch->GetName(), ch->GetMapIndex());
}

void CRespManager::LogoutFromMap(const LPCHARACTER ch)
{
	const auto& mapData = GetMap(ch->GetMapIndex());
	if (!mapData)
		return;

	mapData->LogoutFromMap(ch);

	sys_log(0, "RESP_MANAGER: player %s logout from map %d", ch->GetName(), ch->GetMapIndex());
}

void CRespManager::RegisterMob(const LPCHARACTER ch)
{
	auto& mapData = GetMap(ch->GetMapIndex());
	if (!mapData)
		mapData = RegisterMap(ch->GetMapIndex());

	if ((ch->IsMonster() && ch->GetMobRank() >= MOB_RANK_BOSS) || ch->IsStone())
	{
		const auto& regen = ch->GetRegen();
		if (!regen)
			return;

		const auto& position = ch->GetRegenPos();

		const auto& update = mapData->RegisterMob(regen->id, ch->GetRaceNum(), ch->IsStone(), position.x, position.y, regen->time);
		if (update)
		{
			TEMP_BUFFER buf;

			TPacketGCRespHeader header{};
			header.header = HEADER_GC_RESP;
			header.size = sizeof(TPacketGCRespHeader) + sizeof(TPacketGCRespRefresh);
			header.subheader = RESP_GC_SUBHEADER_REFRESH_RESP;

			TPacketGCRespRefresh pack{};
			pack.id = regen->id;
			pack.vnum = ch->GetRaceNum();
			pack.nextRespTime = 0;
			pack.x = position.x;
			pack.y = position.y;

			buf.write(&header, sizeof(TPacketGCRespHeader));
			buf.write(&pack, sizeof(TPacketGCRespRefresh));

			for (const auto& it : mapData->GetCharacterSet())
			{
				if (!it || !it->GetDesc())
					continue;

				it->GetDesc()->BufferedPacket(buf.read_peek(), buf.size());
			}
		}

		sys_log(0, "RESP_MANAGER: mob %d registered to map %d", ch->GetRaceNum(), ch->GetMapIndex());
	}
}

void CRespManager::KillMob(const LPCHARACTER ch)
{
	const auto& mapData = GetMap(ch->GetMapIndex());
	if (!mapData)
		return;

	const auto& regen = ch->GetRegen();
	if (!regen)
		return;

	const auto& position = ch->GetRegenPos();

	const auto& respTime = mapData->KillMob(regen->id);

	if (!respTime)
		return;

	const auto& characterSet = mapData->GetCharacterSet();

	sys_log(0, "RESP_MANAGER: mob %d killed on map %d, guests %d", ch->GetRaceNum(), ch->GetMapIndex(), characterSet.size());

	TEMP_BUFFER buf;

	TPacketGCRespHeader header{};
	header.header = HEADER_GC_RESP;
	header.size = sizeof(TPacketGCRespHeader) + sizeof(TPacketGCRespRefresh);
	header.subheader = RESP_GC_SUBHEADER_REFRESH_RESP;

	TPacketGCRespRefresh pack{};
	pack.id = regen->id;
	pack.vnum = ch->GetRaceNum();
	pack.nextRespTime = respTime;
	pack.x = position.x;
	pack.y = position.y;

	buf.write(&header, sizeof(TPacketGCRespHeader));
	buf.write(&pack, sizeof(TPacketGCRespRefresh));

	for (const auto& it : mapData->GetCharacterSet())
	{
		if (!it || !it->GetDesc())
			continue;

		it->GetDesc()->BufferedPacket(buf.read_peek(), buf.size());
	}
}

void CRespManager::FetchData(const LPCHARACTER ch, const uint8_t subheader, const uint32_t mobVnum)
{
	const auto& mapData = GetMap(ch->GetMapIndex());
	if (!mapData)
		return;

	if (!mapData->HasMob(mobVnum))
		return;

	TEMP_BUFFER buf;
	buf.write(&mobVnum, sizeof(uint32_t));

	uint8_t outputSubheader = 0;
	uint16_t itemCount = 0;

	if (subheader == RESP_CG_SUBHEADER_FETCH_RESP)
	{
		outputSubheader = RESP_GC_SUBHEADER_DATA_RESP;
		for (const auto& it : mapData->GetRespData())
		{
			const auto& respData = it.second;

			if (respData->vnum != mobVnum)
				continue;

			itemCount++;

			TPacketGCRespData pack{};
			pack.id = it.first;
			pack.x = respData->x;
			pack.y = respData->y;
			pack.time = respData->time;
			pack.nextRespTime = respData->nextRespTime;

			buf.write(&pack, sizeof(TPacketGCRespData));
		}
	}
	else if (subheader == RESP_CG_SUBHEADER_FETCH_DROP)
	{
		outputSubheader = RESP_GC_SUBHEADER_DATA_DROP;

		const CMob* pkMob = CMobManager::instance().Get(mobVnum);
		if (!pkMob)
			return;

		const auto& target = CHARACTER_MANAGER::instance().CreateCharacter(pkMob->m_table.szLocaleName);
		target->SetProto(pkMob);

		std::vector<TDropInfoItem> vecDropInfo;
		const auto bHasDropInfo = ITEM_MANAGER::Instance().CreateDropItemInfo(target, ch, vecDropInfo);
		M2_DESTROY_CHARACTER(target);

		TPacketGCRespGold gold{};
		gold.minGold = pkMob->m_table.dwGoldMin;
		gold.maxGold = pkMob->m_table.dwGoldMax;

		buf.write(&gold, sizeof(TPacketGCRespGold));

		if (bHasDropInfo)
		{
			for (const auto& it : vecDropInfo)
			{
				itemCount++;

				TPacketGCRespItem item{};
				item.vnum = it.dwVnum;
				item.minCount = it.byMinCount;
				item.maxCount = it.byMaxCount;

				buf.write(&item, sizeof(TPacketGCRespItem));
			}
		}
	}

	TPacketGCRespHeader header{};
	header.header = HEADER_GC_RESP;
	header.size = sizeof(TPacketGCRespHeader) + buf.size() + sizeof(uint16_t);
	header.subheader = outputSubheader;

	ch->GetDesc()->BufferedPacket(&header, sizeof(TPacketGCRespHeader));
	ch->GetDesc()->Packet(&itemCount, sizeof(uint16_t));
	ch->GetDesc()->Packet(buf.read_peek(), buf.size());
}

void CRespManager::Teleport(const LPCHARACTER ch, const size_t id)
{
	long mapIndex = ch->GetMapIndex();

	const auto& mapData = GetMap(mapIndex);
	if (!mapData)
		return;

	const auto& respData = mapData->GetRespData(id);
	if (!respData)
		return;

	if (ch->GetDungeon() || ch->GetWarMap() || mapIndex == OXEVENT_MAP_INDEX || mapIndex == marriage::WEDDING_MAP_INDEX)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Resp manager> You cannot teleport on this map."));
		return;
	}

	time_t nextActionTime = ch->GetQuestFlag("__resp_manager.next_action");

	auto deltaTime = nextActionTime - get_global_time();
	if (deltaTime > 0)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Resp manager> Wait %lu seconds."), deltaTime);
		return;
	}


	if (respData->nextRespTime > time(nullptr))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Resp manager> Cannot teleport to target which is not alive."));
		return;
	}

	ch->Show(ch->GetMapIndex(), respData->x + number(-100, 100), respData->y + number(-100, 100));
	ch->Stop();

	ch->SetQuestFlag("__resp_manager.next_action", get_global_time() + RESP_TELEPORT_COOLDOWN);
}
#endif
