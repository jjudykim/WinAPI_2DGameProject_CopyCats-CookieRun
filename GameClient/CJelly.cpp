#include "pch.h"
#include "CJelly.h"

#include "CPathMgr.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CCollider.h"

CJelly::CJelly()
	: m_type(JELLY_TYPE::END)
{
	CJelly(m_type);
	//m_Animator = (CAnimator*)AddComponent(new CAnimator);
	//CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"JelliesAtlasTex", L"texture\\GeneralJellies_Atlas.png");
}

CJelly::CJelly(JELLY_TYPE _type)
	: m_type(_type)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	
	if ((UINT)_type < 5)
	{
		m_Collider->SetScale(Vec2D(30.f, 30.f));
	}
	else
	{
		m_Collider->SetScale(Vec2D(40.f, 50.f));
	}
	
}

CJelly::~CJelly()
{

}

void CJelly::begin()
{
}

void CJelly::tick()
{
}

void CJelly::render()
{
	Vec2D vPos = GetPos();
	Vec2D vScale = GetScale();

	if (m_type == JELLY_TYPE::BLUE_BEAN)
	{
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_BLUE);
		Rectangle(DC, (int)(vPos.x - vScale.x * 0.5f)
			, (int)(vPos.y - vScale.y * 0.5f)
			, (int)(vPos.x + vScale.x * 0.5f)
			, (int)(vPos.y + vScale.y * 0.5f));
	}
	else if (m_type == JELLY_TYPE::PINK_BEAN)
	{
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_RED);
		Rectangle(DC, (int)(vPos.x - vScale.x * 0.5f)
			, (int)(vPos.y - vScale.y * 0.5f)
			, (int)(vPos.x + vScale.x * 0.5f)
			, (int)(vPos.y + vScale.y * 0.5f));
	}
	else if (m_type == JELLY_TYPE::GENERAL_YELLOW_BEAR)
	{
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_GREEN);
		Ellipse(DC, (int)(vPos.x - vScale.x * 0.5f)
			, (int)(vPos.y - vScale.y * 0.5f)
			, (int)(vPos.x + vScale.x * 0.5f)
			, (int)(vPos.y + vScale.y * 0.5f));
	}
	else
	{
		LOG(LOG_TYPE::DBG_ERROR, L"Not defineded Jelly")
	}
}

