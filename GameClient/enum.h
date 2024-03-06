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

	STAGE_01,
	STAGE_02,
	STAGE_03,

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

	UI = 10,
	END = 11,

	NONE = -1,
};

enum class COOKIE_TYPE
{
	BRAVE_COOKIE,
	ANGEL_COOKIE,
	SEAFAIRY_COOKIE,
	KUMIHO_COOKIE,
	END,
};

enum class JELLY_TYPE
{
	// General Jelly
	BLUE_BEAN,
	PINK_BEAN,
	PURPLE_STARCANDY,
	BLUE_STARCANDY,
	CYAN_STARCANDY,

	// Bear Jelly
	GENERAL_YELLOW_BEAR,
	SHY_YELLOW_BEAR,
	GENERAL_PINK_BEAR,
	SHY_PINK_BEAR,

	// Benefit
	SMALL_SILVER_COIN,
	SMALL_GLOD_COIN,
	BIG_GOLD_COIN,

	SMALL_LIFE_POTION,
	BIG_LIFE_POTION,

	// Get Ability
	GET_MAGNETISM,
	GET_DASH,
	GET_LARGE,
	GET_LARGEWITHDASH,

	// Change Obstacle
	CHANGE_TO_COIN,
	CHANGE_TO_BEAR,
	CHANGE_TO_BONUSTIME,

	// Bonus Time
	BONUSTIME,


	END,
};

enum class BACKGROUND_TYPE
{
	MAIN,
	SUB1,
	SUB2,
	SUB3,

	END,
};