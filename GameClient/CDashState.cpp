#include "pch.h"
#include "CDashState.h"

#include "CAnimator.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CDashState::CDashState()
{
}

CDashState::~CDashState()
{
}


void CDashState::Set()
{
	CPlayerState::Set();

	wstring strFilePath = L"animation\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr + L"\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"Dash", strFilePath + L"_Dash.anim");
}

void CDashState::Enter()
{
	GetOwnerAnimator()->Play(L"Dash", true);
}

void CDashState::FinalTick()
{
	CPlayerState::FinalTick();

	if (KEY_TAP(KEY::DOWN) && GetOwnerRigidBody()->IsGround())
	{
		GetFSM()->ChangeState(L"Slide");
	}
	else if (KEY_TAP(KEY::SPACE) || KEY_PRESSED(KEY::SPACE) && GetOwnerRigidBody()->IsGround())
	{
		CPlayer* Player = GetCurPlayer();

		Player->SetJumpStartYPos(Player->GetPos().y);
		Player->SetJumpingState(true);
		Player->PlusJumpCount();
		GetOwnerRigidBody()->Jump();

		GetFSM()->ChangeState(L"Jump");
	}
}

void CDashState::Exit()
{
}


