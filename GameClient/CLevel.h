#pragma once
#include "CEntity.h"

class CObject;
class CCollider;

class CLevel
	: public CEntity
{
	vector<CObject*>    m_vecObj;
	vector<CCollider*>	m_vecCollider;

public:
	void AddObject(CObject* _Object) { m_vecObj.push_back(_Object); }

public:
	virtual void begin();
	virtual void tick();
	virtual void finaltick();
	virtual void render();

public:
	void RegisterCollider(CCollider* _Collider);
public:
	virtual CLevel* Clone() = 0;

public:
	CLevel();
	~CLevel();
};

