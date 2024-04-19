#include "pch.h"
#include "CJumpState.h"

#include "CKeyMgr.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CSound.h"

CJumpState::CJumpState()
	: m_Jumping(false)
	, m_JumpHigherStandard(false)
	, m_JumpStandard(0)
{
}

CJumpState::~CJumpState()
{
}

void CJumpState::Set()
{
	CPlayerState::Set();

	wstring strFilePath = L"animation\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr + L"\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"Jump", strFilePath + L"_Jump.anim");
	SetSoundEffect(CResourceMgr::GetInst()->FindSound(L"Effect_CharJump"));
}

void CJumpState::Enter()
{
	CPlayerState::Enter();

	GetOwnerAnimator()->Play(L"Jump", false);
	GetOwnerRigidBody()->SetUseGravity(true);
	GetSoundEffect()->SetVolume(70.f);
	GetSoundEffect()->Play();
}

void CJumpState::FinalTick()
{
	CPlayerState::FinalTick();

	if (KEY_TAP(KEY::SPACE))
	{
		if ( 0 < GetCurPlayer()->GetCurJumpCount()
			&& GetCurPlayer()->GetCurJumpCount() < 2)
		{
			GetOwnerRigidBody()->Jump();
			GetFSM()->ChangeState(L"DoubleJump");
			
		}
	}
	else if (KEY_TAP(KEY::DOWN) && GetOwnerRigidBody()->IsGround())
	{
		GetFSM()->ChangeState(L"Slide");
	}

	if (GetOwnerRigidBody()->IsDescending())
	{
		GetCurPlayer()->SetJumpingState(false);
	}
	if (!GetCurPlayer()->IsJumping() && GetOwnerRigidBody()->IsGround())
	{
		GetFSM()->ChangeState(L"Run");
	}
}

void CJumpState::Exit()
{
	m_JumpHigherStandard = false;
}

