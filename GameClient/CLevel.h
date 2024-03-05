#pragma once
#include "CEntity.h"

class CObject;
class CCollider;

class CLevel
	: public CEntity
{
	vector<CObject*>    m_arrObj[(UINT)LAYER_TYPE::END];
	vector<CCollider*>	m_arrCollider[(UINT)LAYER_TYPE::END];

public:
	void AddObject(LAYER_TYPE _Layer, CObject* _Object);
	void RegisterCollider(CCollider* _Collider);

public:
	virtual void begin();
	virtual void tick();
	virtual void finaltick();
	virtual void render();

public:
	const vector<CCollider*>& GetColliders(LAYER_TYPE _Layer) { return m_arrCollider[(UINT)_Layer]; }

public:
	virtual CLevel* Clone() = 0;

public:
	CLevel();
	~CLevel();
};

