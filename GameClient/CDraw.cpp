#include "pch.h"
#include "CDraw.h"

#include "CLevelMgr.h"
#include "CMouseMgr.h"
#include "CLevel_Editor.h"

CDraw::CDraw()
	: m_Tex(nullptr)
	, m_Drawing(true)
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

	if (m_Tex == nullptr)
	{
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);
		CSelectObj SelectPen(DC, CEngine::GetInst()->GetPen(PEN_TYPE::PEN_BLUE));

		Rectangle(DC, (int)(vPos.x), (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}
	else
	{
		/*USE_BRUSH(DC, BRUSH_TYPE::BRUSH_BLUE);

		Rectangle(DC, (int)(vPos.x), (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));*/

		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(DC, (int)(vPos.x), (int)(vPos.y)
			, (int)vScale.x, (int)vScale.y
			, m_Tex->GetDC()
			, 0, 0, (int)m_Tex->GetWidth(), (int)m_Tex->GetHeight(), bf);
	}
}
