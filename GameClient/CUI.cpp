#include "pch.h"
#include "CUI.h"

#include "CKeyMgr.h"
#include "CMouseMgr.h"

CUI::CUI()
{
}

CUI::~CUI()
{
}

void CUI::tick()
{
}

void CUI::render()
{
}

void CUI::CheckMouseOn()
{
	Vec2D vPos = GetPos();
	Vec2D vScale = GetScale();
	Vec2D vMousePos = CMouseMgr::GetInst()->GetMousePos();

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
	}
}


