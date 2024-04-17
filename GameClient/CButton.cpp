#include "pch.h"
#include "CButton.h"

#include "CTaskMgr.h"

CButton::CButton()
	: m_Func(nullptr)
	, m_HoverImg(nullptr)
	, m_NormalImg(nullptr)
{
}

CButton::~CButton()
{
}

void CButton::tick_ui()
{
	if (IsLbtnDowned() == true)
	{
		if (m_Func != nullptr)
		{
			m_Func();
			CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::UI_LBTN_DOWN, (DWORD_PTR)this, false });
		}
	}
}

void CButton::render_ui()
{
	CTexture* CurTex = nullptr;

	if (IsLbtnDowned() || IsMouseOn())
	{
		if (m_HoverImg != nullptr)
			CurTex = m_HoverImg;
	}
	else
	{
		if (m_NormalImg != nullptr)
			CurTex = m_NormalImg;
	}

	if (CurTex != nullptr)
	{
		Vec2D vPos = GetFinalPos();
		Vec2D vScale = GetScale();

		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(DC, vPos.x - (vScale.x / 2.f), vPos.y - (vScale.y / 2.f), vScale.x, vScale.y
			, CurTex->GetDC(), 0, 0, CurTex->GetWidth(), CurTex->GetHeight(), bf);
	}
}

void CButton::LButtonClicked()
{
	
}


