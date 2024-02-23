#pragma once
#include "CEntity.h"

class CObject
	: public CEntity
{
private:
	Vec2D      m_Pos;
	Vec2D      m_Scale;

public:
	void SetPos(Vec2D _Pos) { m_Pos = _Pos; }
	void SetPos(float _x, float _y) { m_Pos.x = _x; m_Pos.y = _y; }
	void SetScale(Vec2D _Scale) { m_Scale = _Scale; }
	void SetScale(float _width, float _height) { m_Scale.x = _width; m_Scale.y = _height; }

	Vec2D GetPos() { return m_Pos; }
	Vec2D GetScale() { return m_Scale; }

public:
	virtual void begin();
	virtual void tick();
	virtual void finaltick();
	virtual void render();

public:
	virtual CObject* Clone() = 0;

public:
	CObject();
	~CObject();
};

