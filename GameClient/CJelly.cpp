#include "pch.h"
#include "CJelly.h"

#include "CPathMgr.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CCollider.h"

CJelly::CJelly()
	: m_ObjType(DYNAMIC_OBJ_TYPE::END)
	, m_Index(0)
	, m_Value(0)
	, m_Texture(nullptr)
	, m_Animator(nullptr)
	, m_Collider(nullptr)

{
	SetLayerType(LAYER_TYPE::JELLY);
	m_Animator = nullptr;
	m_Collider = (CCollider*)AddComponent(new CCollider);
}

CJelly::CJelly(const CJelly& _Other)
	: CObject(_Other)
	, m_ObjType(_Other.m_ObjType)
	, m_AtlasInfo(_Other.m_AtlasInfo)
	, m_Index(_Other.m_Index)
	, m_Value(_Other.m_Value)
	, m_Texture(_Other.m_Texture)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
{
	if (_Other.m_Animator != nullptr)
	{
		m_Animator = GetComponent<CAnimator>();
	}
	m_Collider = GetComponent<CCollider>();
}

CJelly::~CJelly()
{

}

void CJelly::begin()
{
	m_Collider->SetScale(Vec2D(GetScale().x, GetScale().y));
}

void CJelly::tick()
{
}

void CJelly::render()
{

}

void CJelly::BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
	// Destroy();
}

