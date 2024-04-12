#include "pch.h"
#include "CJumpState.h"

#include "CKeyMgr.h"

#include "CSound.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"

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
}

void CJumpState::Enter()
{
	CPlayerState::Enter();
	LOG(LOG_TYPE::DBG_WARNING, L"Jump State ÁøÀÔ");

	GetOwnerAnimator()->Play(L"Jump", false);
	CSound* pSound = CResourceMgr::GetInst()->FindSound(L"Effect_CharJump");
	//pSound->Play();

	GetOwnerRigidBody()->SetUseGravity(true);
}

void CJumpState::FinalTick()
{
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

	if (GetOwnerAnimator() != nullptr)
	{
		Vec2D ColPos = GetOwnerAnimator()->GetCurAnim()->GetColliderPos();
		Vec2D ColSize = GetOwnerAnimator()->GetCurAnim()->GetColliderSize();
		GetOwnerCollider()->SetOffsetPos(Vec2D(ColPos.x, ColPos.y - (GetObj()->GetScale().y / 2.f)));
		GetOwnerCollider()->SetScale(GetOwnerAnimator()->GetCurAnim()->GetColliderSize());
	}
}

void CJumpState::Exit()
{
	m_JumpHigherStandard = false;
}

