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
	bool operator <(Vec2D _Other) { return x < _Other.x && y < _Other.y; }
	bool operator <=(Vec2D _Other) { return x <= _Other.x && y <= _Other.y; }

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

	bool operator != (Vec2D _Other)
	{
		if (x == _Other.x && y == _Other.y) { return false; }
		else { return true; }
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

struct Task
{
	TASK_TYPE	Type;
	DWORD_PTR	Param1;
	DWORD_PTR	Param2;
	DWORD_PTR	Param3;
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

struct AniFrm
{
	Vec2D StartPos;
	Vec2D SliceSize;
	Vec2D Offset;
	float Duration;

	AniFrm()
		: StartPos(0)
		, SliceSize(0)
		, Offset(0)
		, Duration(0.f)
	{
	}
	
	AniFrm(const AniFrm& _Other)
		: StartPos(_Other.StartPos)
		, SliceSize(_Other.SliceSize)
		, Offset(_Other.Offset)
		, Duration(_Other.Duration)
	{
	}
};


struct DbgObjInfo
{
	Vec2D			ObjPosition;
	Vec2D			ObjScale;
	wstring         strLog;
};

struct AtlasInfo
{
	Vec2D StartPos;
	Vec2D SliceSize;
};

struct CookieInfo
{
	COOKIE_TYPE _type;
	Vec2D       _frmSize;
	wstring		_nameStr;

	CookieInfo()
		: _type(COOKIE_TYPE::END)
		, _frmSize(0)
		, _nameStr(L"")
	{
	}

	CookieInfo(COOKIE_TYPE _type, Vec2D _size, wstring _name)
		: _type(_type)
		, _frmSize(_size)
		, _nameStr(_name)
	{}
};

struct PetInfo
{
	PET_TYPE _type;
	Vec2D	 _frmSize;
	wstring	 _nameStr;

	PetInfo()
		: _type(PET_TYPE::END)
		, _frmSize(0)
		, _nameStr(L"")
	{
	}

	PetInfo(PET_TYPE _type, Vec2D _size, wstring _name)
		: _type(_type)
		, _frmSize(_size)
		, _nameStr(_name)
	{}
};

struct JellyInfo
{
	UINT	    _type;
	AtlasInfo	_info;
	int			_value;
};

//struct BGInfo
//{
//	BACKGROUND_TYPE		_type;
//	Vec2D				_startPos;
//	Vec2D				_sliceSize;
//	
//};
//
//struct OBSInfo
//{
//	OBS_TYPE	_type;
//	Vec2D		_Pos;
//	wstring		_Path;
//};
//
//struct PLTInfo
//{
//	PLT_TYPE    _type;
//	Vec2D		_Pos;
//	wstring		_Path;
//};

struct StageSTObjInfo
{
	LAYER_TYPE		_objType;
	UINT			_typeIndex;
	Vec2D			_pos;
};

struct StageDNObjInfo
{
	DYNAMIC_OBJ_TYPE	_objType;
	UINT				_typeIndex;
	Vec2D				_pos;
};