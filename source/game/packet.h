// search for:
typedef struct SPacketGCStateCheck
{
	[...]
} TPacketGCStateCheck;

// add under:
#ifdef __ITEM_SHOP__
enum
{
	ITEMSHOP_SUBHEADER_GC_ITEM,
	ITEMSHOP_SUBHEADER_GC_COINS,
	ITEMSHOP_SUBHEADER_GC_CLEAR,
	ITEMSHOP_SUBHEADER_GC_OPEN,
	ITEMSHOP_SUBHEADER_GC_EDITOR,
	ITEMSHOP_SUBHEADER_GC_UPDATE,
	ITEMSHOP_SUBHEADER_GC_DELETE,
	ITEMSHOP_SUBHEADER_GC_ERROR,
	ITEMSHOP_SUBHEADER_GC_BUY_STATS,
	ITEMSHOP_SUBHEADER_GC_LIMITED_COUNT,
	ITEMSHOP_SUBHEADER_GC_REWARD,
	ITEMSHOP_SUBHEADER_GC_REWARD_STATUS,
	ITEMSHOP_SUBHEADER_GC_POPUP,
	ITEMSHOP_SUBHEADER_GC_CATEGORY,

	ITEMSHOP_SUBHEADER_CG_OPEN = 0,
	ITEMSHOP_SUBHEADER_CG_BUY,
	ITEMSHOP_SUBHEADER_CG_ADD,
	ITEMSHOP_SUBHEADER_CG_GET_DAILY_REWARD,

	HEADER_CG_ITEMSHOP = 34,
	HEADER_GC_ITEMSHOP = 139,

	CATEGORY_NAME_MAX_NUM = 32,
};

enum EItemShopError: BYTE
{
	ITEMSHOP_ERROR_NOT_ENOUGH_COINS,
	ITEMSHOP_ERROR_INVENTORY_FULL,
	ITEMSHOP_ERROR_WARP,
	ITEMSHOP_ERROR_NON_EDITOR,
	ITEMSHOP_ERROR_COUNT,
	ITEMSHOP_ERROR_UNKNOWN_ERROR,
};

enum EItemShopPopupType
{
	ITEMSHOP_POPUP_ITEM_PROMO,
	ITEMSHOP_POPUP_ITEM_LIMITED,
	ITEMSHOP_POPUP_NEW_ITEM,
};

typedef struct item_shop_packet
{
	BYTE	header;
	DWORD	size;
	BYTE	subheader;
} TItemShopGCPacket;

typedef struct item_shop_client_packet
{
	BYTE	header;
	BYTE	subheader;
} TItemShopCGPacket;

typedef struct SItemShopItem
{
	DWORD	vnum;
	BYTE	count;
	DWORD	price;
#ifdef __EXTENDED_COIN__
	BYTE	price_type;
#endif
	BYTE	bonus_type;
	BYTE	category;
	DWORD	id;
	long	alSockets[ITEM_SOCKET_MAX_NUM];
	TPlayerItemAttribute	aAttr[ITEM_ATTRIBUTE_MAX_NUM];
	BYTE	is_vip;
	BYTE	fixed_count;
	DWORD	additional_time;
	DWORD	add_time;
	BYTE	discount;
	DWORD	discount_time;
	DWORD	limited_time;
	DWORD	limited_count;
	DWORD	limited_buy_count;
	DWORD	limited_buy_time;

	SItemShopItem()
	{
		vnum = 0;
		price = 0;
#ifdef __EXTENDED_COIN__
		price_type = 0;
#endif
		bonus_type = 0;
		count = 0;
		category = 0;
		id = 0;
		is_vip = false;
		fixed_count = false;
		additional_time = 0;

		add_time = 0;
		discount = 0;
		discount_time = 0;

		limited_time = 0;
		limited_count = 0;
		limited_buy_count = 0;

		limited_buy_time = 0;

		memset(&alSockets, 0, sizeof(alSockets));
		memset(&aAttr, 0, sizeof(aAttr));
	}

} TItemShopItem;

typedef struct item_shop_delete_item
{
	DWORD	id;
	DWORD	category;
} TItemShopItemDeletePacket;

typedef struct item_shop_buy
{
	DWORD	id;
	DWORD	category;
	BYTE	count;
	BYTE	bonus_type;
} TPacketCGItemShopBuy;

typedef struct item_shop_add
{
	TItemShopItem	aItemShopItem;
	BYTE	bFlag;
} TPacketCGItemShopAddItem;

typedef struct item_shop_buy_stats
{
	DWORD	dwID;
	DWORD	dwCategory;
	DWORD	dwCount;

	item_shop_buy_stats(DWORD id, DWORD category)
	{
		dwID = id;
		dwCategory = category;
		dwCount = 1;
	}
	item_shop_buy_stats()
	{
		dwID = 0;
		dwCategory = 0;
		dwCount = 1;
	}
} TItemShopBuyStats;

typedef struct itemshop_open_packet
{
	BYTE	byDailyRewardDay;
	time_t	ttDataTime;
} TItemShopOpenPacket;

typedef struct item_shop_daily_reward
{
	DWORD	dwVnum;
	BYTE	byCount;
} TItemShopDailyReward;

#ifdef __EXTENDED_COIN__
typedef struct item_shop_cash
{
	BYTE	type;
	DWORD	value;
} TItemShopCashPacket;
#endif

typedef struct item_shop_popup_packet
{
	BYTE	type;
	DWORD	id;
	DWORD	category;
} TItemShopPopupPacket;

typedef struct item_shop_category_packet
{
	BYTE index;
	char szName[CATEGORY_NAME_MAX_NUM + 1];
} TItemShopCategoryPacket;
#endif

#ifdef __TOMBOLA__
enum
{
	HEADER_CG_TOMBOLA = 37,
	TOMBOLA_CG_SUBHEADER_START = 0,
	TOMBOLA_CG_SUBHEADER_OPEN = 1,

	HEADER_GC_TOMBOLA = 50,
	TOMBOLA_GC_SUBHEADER_ITEM = 0,
	TOMBOLA_GC_SUBHEADER_START = 1,
	TOMBOLA_GC_SUBHEADER_OPEN = 2,
};

typedef struct tombola_packet
{
	BYTE	byHeader;
	WORD	wSize;
	BYTE	bySubHeader;
} TPacketGCTombola;

typedef struct tombola_client_packet
{
	BYTE	byHeader;
	BYTE	bySubHeader;
} TPacketCGTombola;
#endif