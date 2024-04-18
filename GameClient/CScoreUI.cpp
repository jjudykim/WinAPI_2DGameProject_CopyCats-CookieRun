#include "pch.h"
#include "CScoreUI.h"

CScoreUI::CScoreUI()
{
	for (int i = 0; i < 10; ++i)
	{
		SmallScoreNumber[i] = CResourceMgr::GetInst()->FindTexture(L"SmallScore_" + std::to_wstring(i));
		BigScoreNumber[i] = CResourceMgr::GetInst()->FindTexture(L"BigScore_" + std::to_wstring(i));
	}
}

CScoreUI::~CScoreUI()
{
}

void CScoreUI::tick_ui()
{
}

void CScoreUI::render_ui()
{
	CTexture* tex = GetTexture();

	Vec2D vPos = GetFinalPos();
	Vec2D vScale = GetScale();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC, vPos.x, vPos.y - (vScale.y / 2.f), vScale.x, vScale.y
		, tex->GetDC(), 0, 0, vScale.x, vScale.y, bf);
}


