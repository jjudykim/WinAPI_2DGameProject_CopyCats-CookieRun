#include "pch.h"
#include "CPlatform.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CResourceMgr.h"


CPlatform::CPlatform()
	: m_Texture(nullptr)
	, m_Collider(nullptr)
	, m_Edge(false)
{
	SetLayerType(LAYER_TYPE::PLATFORM);
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(Vec2D(124.f, 120.f));
	m_Collider->SetOffsetPos(Vec2D(0.f, -30.f));
}

CPlatform::CPlatform(const CPlatform& _Other)
	: CObject(_Other)
	, m_Texture(_Other.m_Texture)
	, m_Type(_Other.m_Type)
	, m_Edge(false)
{
	m_Collider = GetComponent<CCollider>();
}

CPlatform::~CPlatform()
{
}

void CPlatform::begin()
{
	m_Collider->SetScale(Vec2D(GetScale().x, GetScale().y / 2.f));
	m_Collider->SetOffsetPos(Vec2D(0.f, GetScale().y / 4.f * (-1.f)));
}

void CPlatform::tick()
{
}

void CPlatform::BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Player")
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
  		pRB->SetGround(true);
		LOG(LOG_TYPE::DBG_LOG, L"SetGround -> true");
	}
}

void CPlatform::OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlatform::EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Player" && m_Edge)
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		pRB->SetGround(false);
		LOG(LOG_TYPE::DBG_LOG, L"SetGround -> false");
	}
}

void CPlatform::render()
{
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC
		, (int)(GetRenderPos().x - m_Texture->GetWidth() / 2.f)
		, (int)(GetRenderPos().y - m_Texture->GetHeight() / 2.f)
		, m_Texture->GetWidth(), m_Texture->GetHeight()
		, m_Texture->GetDC(), 0, 0
		, m_Texture->GetWidth(), m_Texture->GetHeight()
		, bf);
}

