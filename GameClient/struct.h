#pragma once

struct Vec2D
{
public:
	float x;
	float y;

public:
	Vec2D()
		: x(0.f)
		, y(0.f)
	{}

	Vec2D(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2D(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2D(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}

	~Vec2D()
	{}



public:
	Vec2D operator +(float f) { return Vec2D(x + f, y + f); }
	Vec2D operator -(float f) { return Vec2D(x - f, y - f); }
	Vec2D operator *(float f) { return Vec2D(x * f, y * f); }
	Vec2D operator /(float f) { assert(f);  return Vec2D(x / f, y / f); }

	Vec2D operator +(Vec2D _Other) { return Vec2D(x + _Other.x, y + _Other.y); }
	Vec2D operator -(Vec2D _Other) { return Vec2D(x - _Other.x, y - _Other.y); }
	Vec2D operator *(Vec2D _Other) { return Vec2D(x * _Other.x, y * _Other.y); }
	Vec2D operator /(Vec2D _Other) { assert(!(_Other.x == 0.f || _Other.y == 0.f));  return Vec2D(x + _Other.x, y + _Other.y); }

	bool operator == (Vec2D _Other)
	{
		if (x == _Other.x && y == _Other.y) { return true; }
		else { return false; }
	}

	bool operator == (float f)
	{
		if (x == f && y == f) { return true; }
		else { return false; }
	}
};


struct DbgRenderInfo
{
	DBG_SHAPE		Shape;   
	Vec2D		    Position;
	Vec2D		    Scale;   
	PEN_TYPE		Color;   

	float		    Duration;
	float		    Age;     
};


struct DbgLog
{
	LOG_TYPE        Type;
	wstring			strLog;
	float			Age;
};

struct COOKIE_INFO
{
	COOKIE_TYPE _type;
	Vec2D       _frmSize;
	int			_dividerSize;
	wstring		_path;
};

struct JELLY_INFO
{
	JELLY_TYPE	_type;
	Vec2D		_frmSize;
	int			_frmCount;
	int			_dividerSize;
};