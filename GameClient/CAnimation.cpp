#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"

#include "CEngine.h"
#include "CObject.h"
#include "CAnimator.h"
#include "CTexture.h"

CAnimation::CAnimation()
	: m_Animator(nullptr)
	, m_Atlas(nullptr)
	, m_Time(0.f)
	, m_CurFrmIdx(0)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Create(CTexture* _AtlasTex, Vec2D _StartPos, Vec2D _SliceSize, int _DividerSize, int _FrameCount, int _FPS)
{
	m_Atlas = _AtlasTex;

	for (int i = 0; i < _FrameCount; ++i)
	{
		AniFrm frm = {};
		frm.Duration = 0.5f / (float)_FPS;
		frm.StartPos = _StartPos + Vec2D((_SliceSize.x + _DividerSize) * i, 0.f);
		frm.SliceSize = _SliceSize;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::finaltick()
{
	if (m_bFinish)
		return;

	const AniFrm& frm = m_vecFrm[m_CurFrmIdx];

	m_Time += DT;

	if (frm.Duration <= m_Time)
	{
		m_Time -= frm.Duration;
		++m_CurFrmIdx;

		if (m_vecFrm.size() <= m_CurFrmIdx)
		{
			--m_CurFrmIdx;
			m_bFinish = true;
		}
	}
}

void CAnimation::render()
{
	if (m_Atlas == nullptr)
		return;

	const AniFrm& frm = m_vecFrm[m_CurFrmIdx];

	CObject* pOwnerObj = m_Animator->GetOwner();

	Vec2D vRenderPos = pOwnerObj->GetRenderPos();

	TransparentBlt(	  DC
					, (int)(vRenderPos.x - frm.SliceSize.x / 2.f + frm.Offset.x)
					, (int)(vRenderPos.y - frm.SliceSize.y / 2.f + frm.Offset.y)
					, (int)frm.SliceSize.x, (int)frm.SliceSize.y
					, m_Atlas->GetDC()
					, (int)frm.StartPos.x, (int)frm.StartPos.y
					, (int)frm.SliceSize.x, (int)frm.SliceSize.y
					, RGB(0, 0, 0));
}

