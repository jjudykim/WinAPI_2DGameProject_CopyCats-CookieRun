#include "pch.h"
#include "CJelly.h"

#include "CTexture.h"
#include "CPathMgr.h"
#include "CAnimator.h"

CJelly::CJelly()
	: m_type(JELLY_TYPE::END)
{
	//m_Animator = (CAnimator*)AddComponent(new CAnimator);
	
	//CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"JelliesAtlasTex", L"texture\\GeneralJellies_Atlas.png");
}

CJelly::CJelly(JELLY_TYPE _type)
	: m_type(_type)
{
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

