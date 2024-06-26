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
	LOBBY,
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
	EFFECT,
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
	UI_LBTN_DOWN,     // 1 : UI Object Adress, 2 : ture or false;
};

enum class COOKIE_TYPE
{
	BRAVE_COOKIE,
	ANGEL_COOKIE,
	KNIGHT_COOKIE,
	PRINCESS_COOKIE,
	ONION_COOKIE,
	END,
};

enum class PET_TYPE
{
	GOLDDROP,
	FLOWERCOPTER,
	GINGERGHOST,
	FOXYBEAD,
	ONIONFISH,
	GLITTERBALL,
	END,
};

enum class COOKIE_COMPLEX_STATE : int
{
	NONE                = 0, 	
	INVINCIBLE          = 1 << 0,
	BOOST               = 1 << 1, 
	GIANT               = 1 << 2, 
	ATTRACT             = 1 << 3, 
	COINMAGIC           = 1 << 4, 
	GUMMYPARTY          = 1 << 5, 

	END                 = 1 << 8,
};

enum class DYNAMIC_OBJ_TYPE
{
	JELLY,
	COIN,
	BONUSTIME,
	ITEM,

	END,
};

enum class JELLY_TYPE
{
	NORMAL_JELLY,

	SMALL_YELLOW_BEAR,
	BIG_YELLOW_BEAR,
	SMALL_PINK_BEAR,
	BIG_PINK_BEAR,

	END,
};

enum class COIN_TYPE
{
	SMALL_SILVER_COIN,   
	SMALL_GOLD_COIN,
	BIG_GOLD_COIN,

	END,
};

enum class BONUSTIME_TYPE
{
	B, O, N, U, S, T, I, M, E, END,
};

enum class ITEM_TYPE
{
	// Life Potion
	SMALL_LIFE_POTION,
	BIG_LIFE_POTION,

	// Get Ability
	GET_MAGNETISM,
	GET_DASH,
	GET_GIANT,
	GET_DASHWITHGIANT,

	// Change Obstacle To Jelly
	CHANGE_TO_COIN,
	CHANGE_TO_BEAR,
	CHANGE_TO_BONUSTIME,

	END,
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
	END,
};

enum class OBS_TYPE
{
	JUMP_A,
	JUMP_B,
	JUMP_UP,
	JUMP_DOWN,
	DBJUMP_A,
	DBJUMP_B,
	DBJUMP_DOWN,
	DBJUMP_UP,
	SLIDE_A,
	SLIDE_B,
	END,
};

enum class EPISODE_TYPE
{
	EP1,
	EP2,
	EP3,
	EP4,
	EP5,
	END,
};

enum class STAGE_TYPE
{
	STG1,
	STG2,
	STG3,
	STG4,
	STG5,
	STG6,
	END,
};