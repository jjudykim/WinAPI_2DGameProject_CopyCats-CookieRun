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
	m_vecFrm.reserve(10);
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

void CAnimation::Create(CTexture* _AtlasTex, int _FrameCount, const AniFrm& _frm)
{
	m_Atlas = _AtlasTex;

	for (int i = 0; i < _FrameCount; ++i)
	{
		AniFrm frm = {};
		frm.Duration = _frm.Duration;
		frm.StartPos = _frm.StartPos;
		frm.SliceSize = _frm.SliceSize;

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

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC, (int)(vRenderPos.x - frm.SliceSize.x / 2.f + frm.Offset.x)
				 , (int)(vRenderPos.y - frm.SliceSize.y / 2.f + frm.Offset.y)
				 , (int)frm.SliceSize.x, (int)frm.SliceSize.y
				 , m_Atlas->GetDC()
				 , (int)(frm.StartPos.x - frm.SliceSize.x / 2.f), (int)(frm.StartPos.y - frm.SliceSize.y / 2.f)
				 , (int)frm.SliceSize.x, (int)frm.SliceSize.y, bf);
}

void CAnimation::render(int)
{
	if (m_Atlas == nullptr)
		return;

	const AniFrm& frm = m_vecFrm[m_CurFrmIdx];
	Vec2D StartPos = Vec2D(CEngine::GetInst()->GetResolution().x / 4.f, CEngine::GetInst()->GetResolution().y / 2.f);
	Vec2D vRenderPos = CCamera::GetInst()->GetRenderPos(StartPos);

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC, (int)(vRenderPos.x - frm.SliceSize.x / 2.f + frm.Offset.x)
				 , (int)(vRenderPos.y - frm.SliceSize.y / 2.f + frm.Offset.y)
				 , (int)frm.SliceSize.x, (int)frm.SliceSize.y
				 , m_Atlas->GetDC()
				 , (int)(frm.StartPos.x - frm.SliceSize.x / 2.f), (int)(frm.StartPos.y - frm.SliceSize.y / 2.f)
				 , (int)frm.SliceSize.x, (int)frm.SliceSize.y, bf);
}

void CAnimation::render(float)
{
	if (m_Atlas == nullptr)
		return;

	const AniFrm& frm = m_vecFrm[m_CurFrmIdx];
	CObject* pOwnerObj = m_Animator->GetOwner();
	Vec2D vRenderPos = pOwnerObj->GetRenderPos();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC, (int)(vRenderPos.x - frm.SliceSize.x / 2.f + frm.Offset.x)
		, (int)(vRenderPos.y - frm.SliceSize.y + frm.Offset.y)
		, (int)frm.SliceSize.x, (int)frm.SliceSize.y
		, m_Atlas->GetDC()
		, (int)(frm.StartPos.x - frm.SliceSize.x / 2.f), (int)(frm.StartPos.y - frm.SliceSize.y / 2.f)
		, (int)frm.SliceSize.x, (int)frm.SliceSize.y, bf);
}
