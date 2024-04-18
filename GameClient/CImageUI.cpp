#include "pch.h"
#include "CImageUI.h"

#include "CAnimator.h"

CImageUI::CImageUI()
	: m_Anim(nullptr)
	, m_DecreaseUI(false)
{
}

CImageUI::~CImageUI()
{
}

void CImageUI::tick_ui()
{
}

void CImageUI::render_ui()
{
	if (m_Anim != nullptr)
	{
		m_Anim->render(true);
	}
	else if (GetTexture() != nullptr)
	{
		CTexture* tex = GetTexture();

		Vec2D vPos = GetFinalPos();
		Vec2D vScale = GetScale();

		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;

		if (m_DecreaseUI == true)
		{
			AlphaBlend(DC, vPos.x, vPos.y - (vScale.y / 2.f), vScale.x, vScale.y
				, tex->GetDC(), 0, 0, vScale.x, vScale.y, bf);
		}
		else
		{
			AlphaBlend(DC, vPos.x - (vScale.x / 2.f), vPos.y - (vScale.y / 2.f), vScale.x, vScale.y
				, tex->GetDC(), 0, 0, tex->GetWidth(), tex->GetHeight(), bf);
		}
	}
}

void CImageUI::AddAnimator(const wstring& _Key, const wstring& _Path, bool _Repeat)
{
	m_Anim = (CAnimator*)AddComponent(new CAnimator);
	m_Anim->LoadAnimation(_Key, _Path);
	m_Anim->Play(_Key, _Repeat);
}
