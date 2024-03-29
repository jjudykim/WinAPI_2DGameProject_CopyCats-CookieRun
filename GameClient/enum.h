#pragma once

enum class PEN_TYPE
{
	PEN_RED,
	PEN_GREEN,
	PEN_BLUE,
	PEN_BLACK,

	END,
};

enum class BRUSH_TYPE
{
	BRUSH_RED,
	BRUSH_GREEN,
	BRUSH_BLUE,
	
	BRUSH_BLACK,
	BRUSH_WHITE,
	BRUSH_GRAY,
	BRUSH_HOLLOW,

	END,
};

enum class LEVEL_TYPE
{
	LOGO_START,
	EDITOR,
	GAME,
	END,
};

enum class DBG_SHAPE
{
	CIRCLE,
	RECT,
	LINE,
};

enum class LOG_TYPE
{
	DBG_LOG,
	DBG_WARNING,
	DBG_ERROR,
};

enum class LAYER_TYPE
{
	DEFAULT,
	BACKGROUND,
	TILE,
	PLATFORM,
	OBSTACLE,
	JELLY,
	PLAYER,
	DRAW,
	PET,

	UI = 10,
	END = 11,

	NONE = -1,
};

enum class TASK_TYPE
{
	SPAWN_OBJECT,     // 1 : Level, 2 : LAYER_TYPE, 3: Object Adress
	DELETE_OBJECT,    // 1 : Object Adress
	CHANGE_LEVEL,
	CHANGE_CLICKABLE, // 1 : true or false
};

enum class COOKIE_TYPE
{
	BRAVE_COOKIE,
	ANGEL_COOKIE,
	SEAFAIRY_COOKIE,
	KUMIHO_COOKIE,
	END,
};

enum class PET_TYPE
{
	GOLD_DROP,
	GINGER_GHOST,
	FOXY_BEAD,
	MR_FASOLLASI,
	ONION_FISH,
	END,
};

enum class COOKIE_STATE : int
{
	NONE		= 0,
	INVINCIBLE	= 1 << 0,
	BOOST		= 1 << 1,
	GIANT		= 1 << 2,
	ATTRACT     = 1 << 3,
	COINMAGIC   = 1 << 4,
	GUMMYPARTY  = 1 << 5,

	END         = 1 << 7,
};

enum class JELLY_TYPE
{
	NORMAL_JELLY,

	SMALL_YELLOW_BEAR,
	BIG_YELLOW_BEAR,
	SMALL_PINK_BEAR,
	BIG_PINK_BEAR,

	SMALL_SILVER_COIN,
	BIG_SILVER_COIN,
	SMALL_GOLD_COIN,
	BIG_GOLD_COIN,

	// Bonus Time
	BONUSTIME,

	END,
};

enum class ITEM_TYPE
{
	// Life Potion
	SMALL_LIFE_POTION,
	BIG_LIFE_POTION,

	// Get Ability
	GET_MAGNETISM,
	GET_DASH,
	GET_LARGE,

	// Change Obstacle To Jelly
	CHANGE_TO_COIN,
	CHANGE_TO_BEAR,
	CHANGE_TO_BONUSTIME,
};

enum class BG_TYPE
{
	MAIN,
	SUB1,
	SUB2,
	SUB3,

	END,
};

enum class PLT_TYPE
{
	GROUNDED,
	FLOATED,
};

enum class OBS_TYPE
{
	JUMP_NOTI,
	JUMP,
	DBJUMP,
	DOWN,

	END,
};