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
	
	Vec2D(float _f)
		: x(_f)
		, y(_f)
	{}

	Vec2D(int _i)
		: x((float)_i)
		, y((float)_i)
	{}

	~Vec2D()
	{}

public:
	bool IsZero()
	{
		return (x == 0.f && y == 0.f);
	}

	float GetDistance(Vec2D _Other)
	{
		return sqrtf(powf(x - _Other.x, 2) + powf(y - _Other.y, 2));
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	void Normalize()
	{
		assert(!(x == 0.f && y == 0.f));

		float fLen = Length();
		x /= fLen;
		y /= fLen;
	}


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

	void operator += (Vec2D _Other)
	{
		x += _Other.x;
		y += _Other.y;
	}

	void operator += (float f)
	{
		x += f;
		y += f;
	}

	void operator -= (Vec2D _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
	}

	void operator -= (float f)
	{
		x -= f;
		y -= f;
	}

	void operator *= (Vec2D _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
	}

	void operator *= (float f)
	{
		x *= f;
		y *= f;
	}

	void operator /= (Vec2D _Other)
	{
		assert(_Other.x && _Other.y);

		x /= _Other.x;
		y /= _Other.y;
	}

	void operator /= (float f)
	{
		assert(f);

		x /= f;
		y /= f;
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

struct CookieInfo
{
	COOKIE_TYPE _type;
	Vec2D       _frmSize;
	int			_dividerSize;
	wstring		_path;
};

struct JellyInfo
{
	JELLY_TYPE	_type;
	Vec2D		_frmSize;
	int			_frmCount;
	int			_dividerSize;
};

struct BackgroundInfo
{
	BACKGROUND_TYPE		_type;
	Vec2D				_startPos;
	Vec2D				_sliceSize;
};