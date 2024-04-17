#include "pch.h"
#include "CLevel_Logo.h"

#include "CResourceMgr.h"
#include "CCamera.h"

CLevel_Logo::CLevel_Logo()
{
}

CLevel_Logo::~CLevel_Logo()
{
}

void CLevel_Logo::begin()
{
}

void CLevel_Logo::tick()
{
	CLevel::tick();
	
	CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::WHITE_FADE_OUT, 0.2f);
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
	m_CILogo = CResourceMgr::GetInst()->LoadTexture(L"CILogo", L"texture\\Devsisters.png");
}

void CLevel_Logo::Exit()
{
}


