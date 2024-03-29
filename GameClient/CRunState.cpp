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


void CRunState::Set()
{
	CPlayerState::Set();

	wstring strFilePath = L"animation\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr;
	strFilePath += L"\\" + GetCurPlayer()->GetCurCookie()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"Run", strFilePath + L"_Run.anim");
}

void CRunState::Enter()
{
	CPlayerState::Enter();

	GetOwnerAnimator()->Play(L"Run", true);
}

void CRunState::FinalTick()
{
	
}

void CRunState::Exit()
{
}

