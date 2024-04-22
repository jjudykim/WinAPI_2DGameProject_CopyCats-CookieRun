#include "pch.h"
#include "CUI.h"

#include "CKeyMgr.h"
#include "CMouseMgr.h"
#include "CTaskMgr.h"
#include "CTexture.h"

CUI::CUI()
	: m_Tex(nullptr)
	, m_ParentUI(nullptr)
	, m_MouseOn(false)
{
}

CUI::CUI(const CUI& _Origin)
	: CObject(_Origin)
	, m_ParentUI(nullptr)
	, m_MouseOn(false)
{
	for (size_t i = 0; i < _Origin.m_vecChildUI.size(); ++i)
	{
		AddChildUI(_Origin.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Del_Vec(m_vecChildUI);
}

void CUI::tick()
{
	// FinalPos °è»ê
	m_vFinalPos = GetPos();

	if (m_ParentUI)
	{
		m_vFinalPos += m_ParentUI->GetFinalPos();
	}
	m_Boundary = RECT{ (LONG)(m_vFinalPos.x - (GetScale().x / 2.f))
						, (LONG)(m_vFinalPos.y - (GetScale().y / 2.f))
						, (LONG)(m_vFinalPos.x + (GetScale().x / 2.f))
						, (LONG)(m_vFinalPos.y + (GetScale().y / 2.f))};
	CheckMouseOn();

	if (KEY_RELEASED(KEY::LBTN) && CMouseMgr::GetInst()->CheckMouseOnBoundary(m_Boundary))
	{
		CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::UI_LBTN_DOWN, (DWORD_PTR)this, true });
	}

	tick_ui();

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->tick();
	}
}

void CUI::finaltick()
{
	CObject::finaltick();

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finaltick();
	}
}

void CUI::render()
{
	//CObject::render();

	render_ui();

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render();
	}
	
}

void CUI::render_ui()
{
	Vec2D vPos = GetFinalPos();
	Vec2D vScale = GetScale();

	if (m_Tex != nullptr)
	{
		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(DC, vPos.x - (vScale.x / 2.f), vPos.y - (vScale.y / 2.f), vScale.x, vScale.y
					, m_Tex->GetDC(), 0, 0, m_Tex->GetWidth(), m_Tex->GetHeight(), bf);
	}
}

void CUI::CheckMouseOn()
{
	//Vec2D vPos = GetPos();
	//Vec2D vScale = GetScale();
	/*Vec2D vMousePos = CMouseMgr::GetInst()->GetMousePos();

	if (vPos.x <= vMousePos.x &&
		vMousePos.x <= vPos.x + vScale.x &&
		vPos.y <= vMousePos.y &&
		vMousePos.y <= vPos.y + vScale.y)
	{
		m_MouseOn = true;
	}
	else
	{
		m_MouseOn = false;
	}*/

	if (CMouseMgr::GetInst()->CheckMouseOnBoundary(m_Boundary))
	{
		m_MouseOn = true;
	}
	else
	{
		m_MouseOn = false;
	}
	
}

void CUI::LButtonDown()
{
	m_MouseLbtnDown = true;
}

void CUI::LButtonUp()
{
}

void CUI::LButtonClicked()
{
	m_MouseLbtnDown = false;
	m_MouseClicked = true;
}


