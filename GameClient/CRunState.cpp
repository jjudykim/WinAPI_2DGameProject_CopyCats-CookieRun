#include "pch.h"
#include "CRunState.h"

#include "CObject.h"

#include "CPathMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"


CRunState::CRunState()
{
	
}

CRunState::~CRunState()
{
}


void CRunState::Enter()
{
	CPlayerState::Enter();

	wstring strFilePath = L"animation\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr + L"\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"Running", strFilePath + L"_Running");
	CAnimator* anim = GetOwnerAnimator();
	GetOwnerAnimator()->Play(L"Running", true);
}

void CRunState::FinalTick()
{
	
}

void CRunState::Exit()
{
}

