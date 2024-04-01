#include "pch.h"
#include "CJumpState.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"

CJumpState::CJumpState()
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

	GetOwnerRigidBody()->SetUseGravity(true);
	GetOwnerAnimator()->Play(L"Jump", false);
}

void CJumpState::FinalTick()
{
	if (GetOwnerAnimator() != nullptr)
	{
		GetOwnerCollider()->SetOffsetPos(GetOwnerAnimator()->GetCurAnim()->GetColliderPos());
		GetOwnerCollider()->SetScale(GetOwnerAnimator()->GetCurAnim()->GetColliderSize());
	}
}

void CJumpState::Exit()
{
}

