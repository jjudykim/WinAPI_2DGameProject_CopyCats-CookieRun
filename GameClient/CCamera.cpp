#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CTexture.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CPlayer.h"
#include "CTimeMgr.h"

CCamera::CCamera()
	: m_CamSpeed(0.f)
	, m_FadeTex(nullptr)
{
}

CCamera::~CCamera()
{
}

void CCamera::init()
{
	Vec2D vResol = CEngine::GetInst()->GetResolution();

	m_LookAt = Vec2D(vResol.x / 2.f, vResol.y / 2.f);
	m_PrevLookAt = m_LookAt;

	CObject* pObj = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");

	if (pObj != nullptr)
	{
		m_StandardObj = dynamic_cast<CPlayer*>(pObj);
	}
}

void CCamera::tick()
{
	if (m_StandardObj != nullptr)
		m_CamSpeed = m_StandardObj->GetSpeed();

	Move();

	Vec2D vResol = CEngine::GetInst()->GetResolution();
	m_Diff = m_LookAt - Vec2D(vResol.x / 2.f, vResol.y / 2.f);

	CameraEffect();
}

void CCamera::render()
{
	if (m_EffectList.empty())
		return;

	CAM_EFFECT_INFO& info = m_EffectList.front();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)info.Alpha;
	bf.AlphaFormat = 0;

	AlphaBlend(DC, 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight()
				 , m_FadeTex->GetDC(), 0, 0
				 , m_FadeTex->GetWidth(), m_FadeTex->GetHeight(), bf);
}

void CCamera::SetCameraEffect(CAM_EFFECT _Effect, float _Duration)
{
	CAM_EFFECT_INFO info = {};

	info.Effect = _Effect;
	info.Duration = _Duration;
	info.Time = 0.f;
	info.Alpha = 0.f;

	m_EffectList.push_back(info);
}

void CCamera::Move()
{
	m_LookAt.x += m_CamSpeed * DT;
}

void CCamera::CameraEffect()
{
	while (true)
	{
		if (m_EffectList.empty())
			return;

		CAM_EFFECT_INFO& info = m_EffectList.front();
		info.Time += DT;

		if (info.Duration < info.Time)
		{
			m_EffectList.pop_front();
		}
		else
		{
			break;
		}
	}

	CAM_EFFECT_INFO& info = m_EffectList.front();

	if (CAM_EFFECT::FADE_IN == info.Effect)
	{
		info.Alpha = (1.f - (info.Time / info.Duration)) * 255.f;
	}
	else if (CAM_EFFECT::FADE_OUT == info.Effect)
	{
		info.Alpha = (info.Time / info.Duration) * 255.f;
	}
}
