#include "pch.h"
#include "CObstacle.h"

#include "CCollider.h"

CObstacle::CObstacle()
	: m_ObstacleImg(nullptr)
	, m_Collider(nullptr)
{

}

CObstacle::CObstacle(UINT _typeIndex)
{
	SetLayerType(LAYER_TYPE::OBSTACLE);
	m_type = (OBS_TYPE)_typeIndex;

	wstring tPath = L"";
	Vec2D tColliderScale;

	if (m_type == OBS_TYPE::JUMP)
	{
		tPath = L"texture\\Ep1_jump_1.png";
		tColliderScale = Vec2D(80.f, 100.f);
	}
	m_ObstacleImg = CAssetMgr::GetInst()->LoadTexture(L"Ep1_jump_1", tPath);
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(tColliderScale);
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
		, (int)(GetRenderPos().x - m_ObstacleImg->GetWidth() / 2.f)
		, (int)(GetRenderPos().y - m_ObstacleImg->GetHeight() / 2.f)
		, m_ObstacleImg->GetWidth(), m_ObstacleImg->GetHeight()
		, m_ObstacleImg->GetDC(), 0, 0
		, m_ObstacleImg->GetWidth(), m_ObstacleImg->GetHeight()
		, bf);
}

