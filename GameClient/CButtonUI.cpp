#include "pch.h"
#include "CButtonUI.h"

#include "CTaskMgr.h"

CButtonUI::CButtonUI()
	: m_Func(nullptr)
	, m_HoverImg(nullptr)
	, m_NormalImg(nullptr)
	, m_State(0)
{
}

CButtonUI::~CButtonUI()
{
}

void CButtonUI::tick_ui()
{
	if (IsLbtnDowned() || IsMouseOn())
	{
		if (m_HoverImg != nullptr)
			m_State = 1;
	}
	else
	{
		if (m_NormalImg != nullptr)
			m_State = 0;
	}
}

void CButtonUI::render_ui()
{
	CTexture* CurTex = nullptr;

	CurTex = m_State ? m_HoverImg : m_NormalImg;

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

void CButtonUI::LButtonClicked()
{
	if (m_Func != nullptr)
	{
		m_Func();
		CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::UI_LBTN_DOWN, (DWORD_PTR)this, false });
		DoneMouseClickEvent();
	}
	else if (m_FuncWithBtn != nullptr)
	{
		m_FuncWithBtn(this);
		CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::UI_LBTN_DOWN, (DWORD_PTR)this, false });
		DoneMouseClickEvent();
	}
}


