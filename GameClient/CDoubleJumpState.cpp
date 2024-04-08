#include "pch.h"
#include "CDoubleJumpState.h"

#include "CPlayer.h"

#include "CRigidBody.h"
#include "CCollider.h"
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
	if (GetOwnerRigidBody()->IsDescending())
	{
		GetCurPlayer()->SetJumpingState(false);

		if (GetOwnerRigidBody()->IsGround())
		{
			GetFSM()->ChangeState(L"Run");
		}
	}

	if (GetOwnerAnimator() != nullptr)
	{
		Vec2D ColPos = GetOwnerAnimator()->GetCurAnim()->GetColliderPos();
		Vec2D ColSize = GetOwnerAnimator()->GetCurAnim()->GetColliderSize();
		GetOwnerCollider()->SetOffsetPos(Vec2D(ColPos.x, ColPos.y - (GetObj()->GetScale().y / 2.f)));
		GetOwnerCollider()->SetScale(GetOwnerAnimator()->GetCurAnim()->GetColliderSize());
	}
}

void CDoubleJumpState::Exit()
{
}


