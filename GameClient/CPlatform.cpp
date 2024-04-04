#include "pch.h"
#include "CPlatform.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CResourceMgr.h"
#include "CMouseMgr.h"


CPlatform::CPlatform()
	: m_Texture(nullptr)
	, m_Type(PLT_TYPE::END)
	, m_Collider(nullptr)
	, m_Edge(false)
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
	, m_Edge(false)
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

	if (m_Type == PLT_TYPE::GROUNDED)
	{
		AlphaBlend(DC
			, (int)(GetRenderPos().x - m_Texture->GetWidth() / 2.f)
			, (int)(GetRenderPos().y)
			, m_Texture->GetWidth(), m_Texture->GetHeight()
			, m_Texture->GetDC(), 0, 0
			, m_Texture->GetWidth(), m_Texture->GetHeight()
			, bf);
	}
	else if (m_Type == PLT_TYPE::FLOATED)
	{
		AlphaBlend(DC
			, (int)(GetRenderPos().x - m_Texture->GetWidth() / 2.f)
			, (int)(GetRenderPos().y - m_Texture->GetHeight() / 2.f)
			, m_Texture->GetWidth(), m_Texture->GetHeight()
			, m_Texture->GetDC(), 0, 0
			, m_Texture->GetWidth(), m_Texture->GetHeight()
			, bf);
	}
	
}

void CPlatform::CheckMouseOn()
{
	Vec2D vPos = GetRenderPos();
	Vec2D vScale = GetScale();
	Vec2D vMousePos = CMouseMgr::GetInst()->GetMousePos();

	if (m_Type == PLT_TYPE::GROUNDED)
	{
		if (vPos.x - (vScale.x / 2.f) <= vMousePos.x
			&& vMousePos.x <= vPos.x + (vScale.x / 2.f)
			&& vPos.y - vScale.y <= vMousePos.y
			&& vMousePos.y <= vPos.y)
		{
			m_MouseOn = true;
		}
		else
		{
			m_MouseOn = false;
		}
	}
	else if (m_Type == PLT_TYPE::FLOATED)
	{
		if (vPos.x - (vScale.x / 2.f) <= vMousePos.x
			&& vMousePos.x <= vPos.x + (vScale.x / 2.f)
			&& (vPos.y - (vScale.y / 2.f)) <= vMousePos.y
			&& vMousePos.y <= vPos.y + (vScale.y / 2.f))
		{
			m_MouseOn = true;
		}
		else
		{
			m_MouseOn = false;
		}
	}
}
