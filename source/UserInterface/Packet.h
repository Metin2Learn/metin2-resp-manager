// find:
typedef struct SChannelStatus
{
	[...]
} TChannelStatus;

// paste below:
#ifdef ENABLE_RESP_SYSTEM
enum ERespConfig
{
	HEADER_GC_RESP = 158,
	HEADER_CG_RESP = 87,

	RESP_CG_SUBHEADER_FETCH_RESP = 0,
	RESP_CG_SUBHEADER_FETCH_DROP,
	RESP_CG_SUBHEADER_TELEPORT,

	RESP_GC_SUBHEADER_DATA_RESP = 0,
	RESP_GC_SUBHEADER_DATA_DROP,
	RESP_GC_SUBHEADER_DATA_MOB,
	RESP_GC_SUBHEADER_REFRESH_RESP,
};

typedef struct SPacketGCRespHeader
{
	uint8_t	header;
	uint16_t	size;
	uint8_t	subheader;
} TPacketGCRespHeader;

typedef struct SPacketCGRespHeader
{
	uint8_t	header;
	uint8_t	subheader;
} TPacketCGRespHeader;

typedef struct SPacketGCRespData
{
	size_t id;
	uint32_t x;
	uint32_t y;
	uint32_t time;
	uint32_t nextRespTime;
} TPacketGCRespData;

typedef struct SPacketGCRespGold
{
	uint32_t	minGold;
	uint32_t	maxGold;
} TPacketGCRespGold;

typedef struct SPacketGCRespItem
{
	uint32_t	vnum;
	uint8_t	minCount;
	uint8_t	maxCount;
} TPacketGCRespItem;

typedef struct SPacketGCMapData
{
	uint8_t	mobCount;
	uint32_t	currentMetinCount;
	uint32_t	maxMetinCount;
	uint32_t	currentBossCount;
	uint32_t	maxBossCount;
} TPacketGCMapData;

typedef struct SPacketGCRespRefresh
{
	size_t	id;
	uint32_t	vnum;
	time_t	nextRespTime;
	uint32_t	x;
	uint32_t	y;
} TPacketGCRespRefresh;
#endif
