#include "pch.h"
#include "CBackground.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"


CBackground::CBackground()
	: m_type()
{
	
}

CBackground::CBackground(UINT _typeIndex)
	: CObject()
{
	SetLayerType(LAYER_TYPE::BACKGROUND);
	m_type = (BG_TYPE)_typeIndex;
	/*wstring Path = L"";
	LEVEL_TYPE CurLevel = GET_CUR_LEVELTYPE;

	if (CurLevel == LEVEL_TYPE::STAGE_01)
	{
		Path = L"texture\\Ep1_Background_Atlas.png";
	}
	m_BackGroundImg = CAssetMgr::GetInst()->LoadTexture(L"Ep1_BackgroundAtlasTex", Path);*/
}

CBackground::~CBackground()
{
	
}

//void CBackground::SetBackgroundInfo(BACKGROUND_TYPE _type)
//{
//	Vec2D tStartPos;
//	Vec2D tSlicePos;
//
//	LEVEL_TYPE CurLevel = GET_CUR_LEVELTYPE;
//
//	if (CurLevel == LEVEL_TYPE::STAGE_01)
//	{
//		if (_type == BACKGROUND_TYPE::MAIN)
//		{
//			tStartPos = Vec2D(2.0f, 17.0f);
//			tSlicePos = Vec2D(569.f, 320.f);
//			//m_Speed = 0.f;
//		}
//		else if (_type == BACKGROUND_TYPE::SUB1)
//		{
//			tStartPos = Vec2D(573.f, 17.0f);
//			tSlicePos = Vec2D(862.f, 320.f);
//			//m_Speed = 10.f;
//		}
//	}
//
//	m_Info = BGInfo{ _type, tStartPos, tSlicePos };
//}

void CBackground::tick()
{
	Vec2D tPos = GetPos();

	tPos.x -= GetSpeed() * DT;

	SetPos(tPos);
}

void CBackground::render()
{

	AtlasInfo info = GetAtlasInfo();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC
				, (int)(GetRenderPos().x)
				, (int)(GetRenderPos().y)
				, (int)info.SliceSize.x * 2.25f, (int)info.SliceSize.y * 2.25f
				, GetImage()->GetDC()
				, (int)info.StartPos.x, (int)info.StartPos.y
				, (int)info.SliceSize.x, (int)info.SliceSize.y
				, bf);
}
