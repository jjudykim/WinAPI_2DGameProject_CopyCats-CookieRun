#include "pch.h"
#include "CDoubleJumpState.h"

#include "CPlayer.h"
#include "CAnimator.h"
#include "CAnimation.h"

CDoubleJumpState::CDoubleJumpState()
{
	
}

CDoubleJumpState::~CDoubleJumpState()
{
}

void CDoubleJumpState::Set()
{
	CPlayerState::Set();

	wstring strFilePath = L"animation\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr;
	strFilePath += L"\\" + GetCurPlayer()->GetCurCookie()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"DoubleJump", strFilePath + L"_DoubleJump.anim");
}

void CDoubleJumpState::Enter()
{
	GetOwnerAnimator()->Play(L"DoubleJump", false);
}

void CDoubleJumpState::FinalTick()
{
}

void CDoubleJumpState::Exit()
{
}


