#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CTexture.h"
#include "CTimeMgr.h"

CCamera::CCamera()
	: m_CamSpeed(1.35f)
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
}

void CCamera::tick()
{
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
	m_LookAt.x += DT * 0.2f;
	wstring m_DiffStr = wstring(L"Now m_Diff : ") + std::to_wstring(m_Diff.x);
	if (m_Time > 1.0f)
	{
		DebugLog(LOG_TYPE::DBG_WARNING, m_DiffStr);
		m_Time = 0;
	}
	m_Time += DT;
	
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
