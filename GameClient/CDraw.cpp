#include "pch.h"
#include "CDraw.h"

#include "CLevelMgr.h"
#include "CMouseMgr.h"
#include "CLevel_Editor.h"

CDraw::CDraw()
	: m_Drawing(true)
{
}

CDraw::~CDraw()
{
}

void CDraw::tick()
{
	if (m_Drawing)
	{
		if (CMouseMgr::GetInst()->IsLbtnDowned())
		{
			Vec2D CurPos = CMouseMgr::GetInst()->GetMousePos();
			CurPos = CCamera::GetInst()->GetRealPos(CurPos);
			Vec2D Drag = CurPos - this->GetPos();
			this->SetScale(Drag);
		}
		else
		{
			m_Drawing = false;
		}
	}
	
}

void CDraw::render()
{
	Vec2D vPos = GetRenderPos();
	Vec2D vScale = GetScale();

	USE_PEN(DC, PEN_TYPE::PEN_BLUE);

	Rectangle(DC, (int)(vPos.x), (int)(vPos.y)
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));
}
