#include "pch.h"
#include "CPlatform.h"

#include "CDbgRenderMgr.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CResourceMgr.h"
#include "CMouseMgr.h"


CPlatform::CPlatform()
	: m_Texture(nullptr)
	, m_Type(PLT_TYPE::END)
	, m_Collider(nullptr)
	, m_UseMouse(false)
	, m_MouseOn(false)
{
	SetLayerType(LAYER_TYPE::PLATFORM);
	m_Collider = (CCollider*)AddComponent(new CCollider);
}

CPlatform::CPlatform(const CPlatform& _Other)
	: CObject(_Other)
	, m_Texture(_Other.m_Texture)
	, m_Type(_Other.m_Type)
	, m_UseMouse(_Other.m_UseMouse)
	, m_MouseOn(false)
{
	m_Collider = GetComponent<CCollider>();
}

CPlatform::~CPlatform()
{
}

void CPlatform::begin()
{
	m_Collider->SetScale(Vec2D(GetScale().x, GetScale().y));
}

void CPlatform::tick()
{
	if (m_UseMouse)
	{
		CheckMouseOn();
	}
}

void CPlatform::BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
	
}

void CPlatform::OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlatform::EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
	
}

void CPlatform::render()
{	
	if (!(RENDER_MINPOSX <= (GetPos().x + GetScale().x) && GetPos().x - GetScale().x <= RENDER_MAXPOSX)) return;

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC
		, (int)(GetRenderPos().x - m_Texture->GetWidth() / 2.f)
		, (int)(GetRenderPos().y)
		, m_Texture->GetWidth(), m_Texture->GetHeight()
		, m_Texture->GetDC(), 0, 0
		, m_Texture->GetWidth(), m_Texture->GetHeight()
		, bf);
}

void CPlatform::CheckMouseOn()
{
	Vec2D vPos = GetRenderPos();
	Vec2D vScale = GetScale();
	Vec2D vMousePos = CMouseMgr::GetInst()->GetMousePos();

	if (vPos.x - (vScale.x / 2.f) <= vMousePos.x
		&& vMousePos.x <= vPos.x + (vScale.x / 2.f)
		&& vPos.y <= vMousePos.y
		&& vMousePos.y <= vPos.y + vScale.y)
	{
		m_MouseOn = true;
	}
	else
	{
		m_MouseOn = false;
	}
}
