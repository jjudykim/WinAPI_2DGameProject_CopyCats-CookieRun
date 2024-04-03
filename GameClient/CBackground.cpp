#include "pch.h"
#include "CBackground.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"


CBackground::CBackground()
	: m_type()
	, m_BGAtlas(nullptr)
{
	SetLayerType(LAYER_TYPE::BACKGROUND);
}

CBackground::CBackground(const CBackground& _Other)
	: CObject(_Other)
	, m_type(_Other.m_type)
	, m_BGAtlas(_Other.m_BGAtlas)
	, m_AtlasInfo(_Other.m_AtlasInfo)
{
}

CBackground::~CBackground()
{
	
}

void CBackground::SetAtlasInfo(Vec2D _StartPos, Vec2D _SliceSize)
{
	m_AtlasInfo.StartPos = _StartPos;
	m_AtlasInfo.SliceSize = _SliceSize;
}

void CBackground::tick()
{
	Vec2D tPos = GetPos();

	tPos.x -= GetSpeed() * DT;

	SetPos(tPos);
}

void CBackground::render()
{
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC
				, (int)(GetRenderPos().x)
				, (int)(GetRenderPos().y)
				, (int)m_AtlasInfo.SliceSize.x * 2.25f, (int)m_AtlasInfo.SliceSize.y * 2.25f
				, m_BGAtlas->GetDC()
				, (int)m_AtlasInfo.StartPos.x, (int)m_AtlasInfo.StartPos.y
				, (int)m_AtlasInfo.SliceSize.x, (int)m_AtlasInfo.SliceSize.y
				, bf);
}
