#pragma once
#include "CEntity.h"

#include "CEngine.h"
#include "CAssetMgr.h"
#include "CCamera.h"
#include "CTexture.h"

class CComponent;
class CAnimator;
class CCollider;

class CObject
	: public CEntity
{
private:
	Vec2D				m_Pos;
	Vec2D				m_Scale;
	float               m_Speed;
	vector<CComponent*> m_vecCom;

	CAnimator*			m_Animator;
	CTexture*			m_Image;
	AtlasInfo			m_ImageInfo;

	LAYER_TYPE          m_Type;
	bool				m_bDead;

protected:


public:
	void SetPos(Vec2D _Pos) { m_Pos = _Pos; }
	void SetPos(float _x, float _y) { m_Pos.x = _x; m_Pos.y = _y; }
	void SetSpeed(float _speed) { m_Speed = _speed; }
	void SetScale(Vec2D _Scale) { m_Scale = _Scale; }
	void SetScale(float _width, float _height) { m_Scale.x = _width; m_Scale.y = _height; }
	void SetImage(CTexture* _image) { m_Image = _image; }
	void SetAtlasInfo(bool _use, Vec2D _StartPos, Vec2D _SlicePos);
	void SetLayerType(LAYER_TYPE _type) { m_Type = _type; }
	
	Vec2D GetPos() { return m_Pos; }
	Vec2D GetScale() { return m_Scale; }
	float GetSpeed() { return m_Speed; }
	Vec2D GetRenderPos() { return CCamera::GetInst()->GetRenderPos(m_Pos); }
	CTexture* GetImage() { return m_Image; }
	AtlasInfo GetAtlasInfo() { return m_ImageInfo; }
	LAYER_TYPE GetLayerType() { return m_Type; }
	
	bool IsDead() { return m_bDead; }

	void Destroy();
	
public:
	virtual void begin();
	virtual void tick();
	virtual void finaltick();
	virtual void render();

	virtual void BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) {}
	virtual void OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) {}
	virtual void EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) {}

	


public:
	CComponent* AddComponent(CComponent* _Component);

	template<typename T>
	T* GetComponent()
	{
		for (size_t i = 0; i < m_vecCom.size(); ++i)
		{
			T* pComponent = dynamic_cast<T*>(m_vecCom[i]);

			if (pComponent)
			{
				return pComponent;
			}
		}
		return nullptr;
	}


public:
	virtual CObject* Clone() = 0;

public:
	CObject();
	CObject(const CObject& _Other);
	~CObject();

	friend class CLevel;
	friend class CTaskMgr;
};

