#include "pch.h"
#include "CPlatform.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAssetMgr.h"


CPlatform::CPlatform()
{
	
}

CPlatform::CPlatform(PLATFORM_TYPE _type)
{
	wstring tPath = L"";

	if (_type == PLATFORM_TYPE::GROUNDED)
	{
		tPath = L"texture\\Ep1_grounded_Platform.png";
	}
	m_PlatformImg = CAssetMgr::GetInst()->LoadTexture(L"Grounded_Platform_Img", tPath);
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(Vec2D(124.f, 120.f));
	m_Collider->SetOffsetPos(Vec2D(0.f, -30.f));
	
}

CPlatform::CPlatform(const CPlatform& _Other)
	: CObject(_Other)
	, m_PlatformImg(_Other.m_PlatformImg)
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
	Vec2D vPos = GetRenderPos();

	SetPos(vPos);
}

void CPlatform::BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Player")
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
  		pRB->SetGround(true);
	}
}

void CPlatform::OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlatform::EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlatform::render()
{
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC
		, (int)(GetPos().x - m_PlatformImg->GetWidth() / 2.f)
		, (int)(GetPos().y - m_PlatformImg->GetHeight() / 2.f)
		, m_PlatformImg->GetWidth(), m_PlatformImg->GetHeight()
		, m_PlatformImg->GetDC(), 0, 0
		, m_PlatformImg->GetWidth(), m_PlatformImg->GetHeight()
		, bf);
}

