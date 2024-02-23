#pragma once
#include "CEntity.h"

class CObject;

class CLevel
	: public CEntity
{
	vector<CObject*>    m_vecObj;

public:
	void AddObject(CObject* _Object) { m_vecObj.push_back(_Object); }

public:
	virtual void begin();
	virtual void tick();
	virtual void finaltick();
	virtual void render();

public:
	CLevel();
	~CLevel();
};

