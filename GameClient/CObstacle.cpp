#include "pch.h"
#include "CObstacle.h"

#include "CCollider.h"
#include "CAnimator.h"

CObstacle::CObstacle()
	: m_Texture(nullptr)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_type(OBS_TYPE::END)
{
	SetLayerType(LAYER_TYPE::OBSTACLE);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_Collider = (CCollider*)AddComponent(new CCollider);
}

CObstacle::CObstacle(const CObstacle& _Other)
	: CObject(_Other)
	, m_type(_Other.m_type)
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

CObstacle::~CObstacle()
{
}


void CObstacle::begin()
{
}

void CObstacle::tick()
{
}

void CObstacle::render()
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

