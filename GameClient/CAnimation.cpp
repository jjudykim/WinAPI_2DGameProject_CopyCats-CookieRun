#include "pch.h"
#include "CAnimation.h"

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

void CAnimation::Create(CTexture* _AtlasTex, Vec2D _StartPos, Vec2D _SliceSize, int _FrameCount, int _FPS)
{
	m_Atlas = _AtlasTex;

	for (int i = 0; i < _FrameCount; ++i)
	{
		AniFrm frm = {};
		frm.Duration = 0.5f / (float)_FPS;
		frm.StartPos = _StartPos + Vec2D(_SliceSize.x * i, 0.f);
		frm.SliceSize = _SliceSize;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::finaltick()
{
}

void CAnimation::render()
{
	if (m_Atlas == nullptr)
		return;

	const AniFrm& frm = m_vecFrm[m_CurFrmIdx];

	CObject* pOwnerObj = m_Animator->GetOwner();

	Vec2D vPos = pOwnerObj->GetPos();

	TransparentBlt(	  DC
					, (int)(vPos.x - frm.SliceSize.x / 2.f + frm.Offset.x)
					, (int)(vPos.y - frm.SliceSize.y / 2.f + frm.Offset.y)
					, (int)frm.SliceSize.x, (int)frm.SliceSize.y
					, m_Atlas->GetDC()
					, (int)frm.StartPos.x, (int)frm.StartPos.y
					, (int)frm.SliceSize.x, (int)frm.SliceSize.y
					, RGB(255, 0, 0));
}

