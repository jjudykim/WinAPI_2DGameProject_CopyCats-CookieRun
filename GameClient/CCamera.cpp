#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CTexture.h"
#include "CLevelMgr.h"
#include "CKeyMgr.h"
#include "CLevel.h"
#include "CLevel_Editor.h"
#include "CPlayer.h"
#include "CTimeMgr.h"

CCamera::CCamera()
	: m_CamSpeed(0.f)
	, m_FadeTex(nullptr)
	, m_FocusObj(nullptr)
	, m_LimitPosX(FLT_MAX)
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
}

void CCamera::tick()
{
	CLevel* pLevel = GET_CUR_LEVEL;
	LEVEL_TYPE curLevel = GET_CUR_LEVELTYPE;
	
	if (curLevel == LEVEL_TYPE::GAME)
	{
		if (m_FocusObj != nullptr)
			m_CamSpeed = m_FocusObj->GetSpeed();
		m_LookAt.x += m_CamSpeed * DT;
	}
	else if (curLevel == LEVEL_TYPE::EDITOR)
	{
		m_CamSpeed = 500.f;
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		if (pEditorLevel->GetEditMode() == 0)
		{
			MoveAll();
		}
		else if (pEditorLevel->GetEditMode() == 1 || pEditorLevel->GetEditMode() == 2)
		{
			MoveLR();
		}
	}

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

void CCamera::SetCameraDefault()
{
	init();
	m_Diff = 0;
}

void CCamera::SetCameraFocus()
{
	CObject* pObj = GET_CUR_LEVEL->FindObjectByName(L"Player");

	if (pObj != nullptr)
	{
		m_FocusObj = dynamic_cast<CPlayer*>(pObj);
	}
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

void CCamera::MoveAll()
{
	if (KEY_PRESSED(KEY::W))
		m_LookAt.y -= DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::S))
		m_LookAt.y += DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::A))
		m_LookAt.x -= DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::D))
		m_LookAt.x += DT * m_CamSpeed;
}

void CCamera::MoveLR()
{
	if (KEY_PRESSED(KEY::A) && (CEngine::GetInst()->GetResolution().x / 2.f < m_LookAt.x))
		m_LookAt.x -= DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::D) && (m_LookAt.x < m_LimitPosX - CEngine::GetInst()->GetResolution().x / 2.f))
		m_LookAt.x += DT * m_CamSpeed;
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
