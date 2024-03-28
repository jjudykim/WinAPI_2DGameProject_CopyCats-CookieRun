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

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"animation\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"Running", strFilePath);
	GetOwnerAnimator()->Play(L"Running", true);
}

void CRunState::FinalTick()
{
	
}

void CRunState::Exit()
{
}

