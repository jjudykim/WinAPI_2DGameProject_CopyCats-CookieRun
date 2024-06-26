#pragma once
#include "CEntity.h"

class CObject;
class CCollider;
class CAnimator;

class CLevel
	: public CEntity
{
protected:
	vector<CObject*>    m_arrObj[(UINT)LAYER_TYPE::END];
	vector<CCollider*>	m_arrCollider[(UINT)LAYER_TYPE::END];
	vector<CAnimator*>  m_arrAnimator[(UINT)LAYER_TYPE::END];

public:
	void AddObject(LAYER_TYPE _Layer, CObject* _Object);
	void RegisterCollider(CCollider* _Collider);
	CObject* FindObjectByName(const wstring& _Name);
	CObject* FindObjectByName(LAYER_TYPE _Type, const wstring& _Name);


public:
	virtual void begin();
	virtual void tick();
	virtual void finaltick();
	virtual void render();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	const vector<CObject*>& GetObjectsByLayerType(LAYER_TYPE _Type) { return m_arrObj[(UINT)_Type]; }
	const vector<CCollider*>& GetColliders(LAYER_TYPE _Layer) { return m_arrCollider[(UINT)_Layer]; }
	const vector<CAnimator*>& GetAnimators(LAYER_TYPE _Layer) { return m_arrAnimator[(UINT)_Layer]; }

	void SortObjectsByXpos(LAYER_TYPE _Layer);
public:
	virtual CLevel* Clone() = 0;

public:
	CLevel();
	~CLevel();

	friend class CUIMgr;
};

