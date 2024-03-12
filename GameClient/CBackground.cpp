#include "pch.h"
#include "CBackground.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"


CBackground::CBackground()
	: m_BackGroundImg(nullptr)
{
	
}

CBackground::CBackground(BACKGROUND_TYPE _BGtype)
	: CObject()
{
	wstring Path = L"";
	LEVEL_TYPE CurLevel = GET_CUR_LEVELTYPE;

	if (CurLevel == LEVEL_TYPE::STAGE_01)
	{
		Path = L"texture\\Ep1_Background_Atlas.png";
	}
	m_BackGroundImg = CAssetMgr::GetInst()->LoadTexture(L"Ep1_BackgroundAtlasTex", Path);
	
	SetBackgroundInfo(_BGtype);
}

CBackground::~CBackground()
{
	
}

void CBackground::SetBackgroundInfo(BACKGROUND_TYPE _type)
{
	Vec2D tStartPos;
	Vec2D tSlicePos;

	LEVEL_TYPE CurLevel = GET_CUR_LEVELTYPE;

	if (CurLevel == LEVEL_TYPE::STAGE_01)
	{
		if (_type == BACKGROUND_TYPE::MAIN)
		{
			tStartPos = Vec2D(2.0f, 17.0f);
			tSlicePos = Vec2D(569.f, 320.f);
			//m_Speed = 0.f;
		}
		else if (_type == BACKGROUND_TYPE::SUB1)
		{
			tStartPos = Vec2D(573.f, 17.0f);
			tSlicePos = Vec2D(862.f, 320.f);
			//m_Speed = 10.f;
		}
	}

	m_Info = BGInfo{ _type, tStartPos, tSlicePos };
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
				, (int)m_Info._sliceSize.x * 2.25f, (int)m_Info._sliceSize.y * 2.25f
				, m_BackGroundImg->GetDC()
				, (int)m_Info._startPos.x, (int)m_Info._startPos.y
				, (int)m_Info._sliceSize.x, (int)m_Info._sliceSize.y
				, bf);
}