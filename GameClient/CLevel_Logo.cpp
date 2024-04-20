#include "pch.h"
#include "CLevel_Logo.h"

#include "CResourceMgr.h"
#include "CTaskMgr.h"
#include "CLevelMgr.h"
#include "CCamera.h"
#include "CTimeMgr.h"
#include "CImageUI.h"
#include "CSound.h"
#include "CButtonUI.h"

void EditModeBtnCallBackFunc()
{
	CSound* sound = CResourceMgr::GetInst()->FindSound(L"Effect_UIBtn");
	sound->SetVolume(80.f);
	sound->Play();
	CLevelMgr::GetInst()->ChangeLevel(LEVEL_TYPE::EDITOR);
}

void GameStartBtnCallBackFunc()
{
	CSound* sound = CResourceMgr::GetInst()->FindSound(L"Effect_UIBtn");
	sound->SetVolume(80.f);
	sound->Play();
	CLevelMgr::GetInst()->ChangeLevel(LEVEL_TYPE::LOBBY);
}

CLevel_Logo::CLevel_Logo()
	: m_OpeningDone{0}
	, m_StartGame(0)
{
}

CLevel_Logo::~CLevel_Logo()
{
}

void CLevel_Logo::begin()
{
	CTimeMgr::GetInst()->AddTimer(1.f, [this]() {}, false);

	CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::WHITE_FADE_IN, 0.5f);
	CSound* sound = CResourceMgr::GetInst()->FindSound(L"Opening_CISound");
	sound->SetVolume(70.f);
	sound->Play();

	CTimeMgr::GetInst()->AddTimer(3.f, [this]() {
		CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::WHITE_FADE_OUT, 0.5f);
		CTimeMgr::GetInst()->AddTimer(0.5f, [this]() {
			m_OpeningDone[0] = true; 
			}, false);
		
		}, false);
}

void CLevel_Logo::tick()
{
	CLevel::tick();

	if (!m_StartGame)
	{
		if (m_OpeningDone[2] == true)
		{
			m_Logo = new CImageUI;
			m_Logo->SetTexture(CResourceMgr::GetInst()->FindTexture(L"Opening_Logo"));
			m_Logo->SetScale(m_Logo->GetTexture()->GetWidth(), m_Logo->GetTexture()->GetHeight());
			m_Logo->SetPos(CEngine::GetInst()->GetResolution().x / 2.f, CEngine::GetInst()->GetResolution().y - 300.f);
			AddObject(LAYER_TYPE::DEFAULT, m_Logo);
			AddObject(LAYER_TYPE::UI, m_BtnEditMode);
			AddObject(LAYER_TYPE::UI, m_BtnGameStart);
			m_StartGame = true;
		}
		else if (m_OpeningDone[1] == true)
		{
			CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::WHITE_FADE_IN, 0.3f);
			m_CurBG->SetTexture(CResourceMgr::GetInst()->FindTexture(L"Opening_BG"));
			m_CurBG->SetScale(m_CurBG->GetTexture()->GetWidth(), m_CurBG->GetTexture()->GetHeight());
			CSound* sound = CResourceMgr::GetInst()->FindSound(L"Opening_Main");
			sound->SetVolume(50.f);
			sound->Play();
			m_OpeningDone[2] = true;
		}
		else if (m_OpeningDone[0] == true)
		{
			m_CurBG->SetTexture(CResourceMgr::GetInst()->FindTexture(L"WhiteTexture"));

			CTimeMgr::GetInst()->AddTimer(1.f, [this]() {
				m_OpeningDone[1] = true;
				}, false);
		}
	}
	else
	{
		
	}
}

void CLevel_Logo::finaltick()
{
}

void CLevel_Logo::render()
{
	CLevel::render();
}

void CLevel_Logo::Enter()
{
	m_Resolution = CEngine::GetInst()->GetResolution();
	CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::CHANGE_CLICKABLE, true });

	CResourceMgr::GetInst()->LoadTexture(L"CILogo", L"texture\\CILogo.png");
	CResourceMgr::GetInst()->LoadTexture(L"Opening_BG", L"texture\\Opening_BG.png");
	CResourceMgr::GetInst()->LoadTexture(L"Opening_Logo", L"texture\\Opening_Logo.png");

	// SoundLoad
	CResourceMgr::GetInst()->LoadSound(L"Opening_CISound", L"sound\\Opening_CISound.wav");
	CResourceMgr::GetInst()->LoadSound(L"Opening_Main", L"sound\\Opening_Main.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_UIBtn", L"sound\\Effect_UIButton.wav");

	// First UI
	m_CurBG = new CImageUI;
	m_CurBG->SetTexture(CResourceMgr::GetInst()->FindTexture(L"CILogo"));
	m_CurBG->SetScale(m_CurBG->GetTexture()->GetWidth(), m_CurBG->GetTexture()->GetHeight());
	m_CurBG->SetPos(m_Resolution.x / 2.f, m_Resolution.y / 2.f);
	AddObject(LAYER_TYPE::DEFAULT, m_CurBG);

	// Setting Button
	m_BtnEditMode = new CButtonUI;
	m_BtnEditMode->SetCallBack(&EditModeBtnCallBackFunc);
	m_BtnEditMode->SetScale(260.f, 110.f);
	m_BtnEditMode->SetPos(m_Resolution.x / 3.f, m_Resolution.y - (m_Resolution.y/ 6.f));
	m_BtnEditMode->SetHoverImage(CResourceMgr::GetInst()->LoadTexture(L"EditModeBtn_Hover", L"texture\\Button\\EditMode_Hover.png"));
	m_BtnEditMode->SetNormalImage(CResourceMgr::GetInst()->LoadTexture(L"EditModeBtn_Normal", L"texture\\Button\\EditMode_Normal.png"));

	m_BtnGameStart = new CButtonUI;
	m_BtnGameStart->SetCallBack(&GameStartBtnCallBackFunc);
	m_BtnGameStart->SetScale(260.f, 110.f);
	m_BtnGameStart->SetPos((m_Resolution.x / 3.f) * 2.f, m_Resolution.y - (m_Resolution.y / 6.f));
	m_BtnGameStart->SetHoverImage(CResourceMgr::GetInst()->LoadTexture(L"GameStartBtn_Hover", L"texture\\Button\\GameStart_Hover.png"));
	m_BtnGameStart->SetNormalImage(CResourceMgr::GetInst()->LoadTexture(L"GameStartBtn_Normal", L"texture\\Button\\GameStart_Normal.png"));
}

void CLevel_Logo::Exit()
{
	CResourceMgr::GetInst()->FindSound(L"Opening_Main")->Stop();
}


