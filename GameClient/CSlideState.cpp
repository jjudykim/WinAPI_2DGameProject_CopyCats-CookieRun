#include "pch.h"
#include "CSlideState.h"

#include "CKeyMgr.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"

CSlideState::CSlideState()
{
}

CSlideState::~CSlideState()
{
}

void CSlideState::Set()
{
	CPlayerState::Set();

	wstring strFilePath = L"animation\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr;
	strFilePath += L"\\" + GetCurPlayer()->GetCurCookie()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"Slide", strFilePath + L"_Slide.anim");
}

void CSlideState::Enter()
{
	CPlayerState::Enter();
	LOG(LOG_TYPE::DBG_WARNING, L"Slide State ÁøÀÔ");
	GetOwnerRigidBody()->SetUseGravity(true);
	GetOwnerAnimator()->Play(L"Slide", true);
}

void CSlideState::FinalTick()
{
	/*if (KEY_TAP(KEY::SPACE))
	{
		CPlayer* Player = GetCurPlayer();

		Player->SetJumpStartYPos(Player->GetPos().y);
		Player->SetJumpingState(true);
		int count = Player->GetCurJumpCount();
		GetOwnerRigidBody()->Jump();
		
		GetFSM()->ChangeState(L"Jump");
	}*/
	if (KEY_RELEASED(KEY::DOWN))
	{
		if (KEY_TAP(KEY::SPACE) || KEY_PRESSED(KEY::SPACE) && GetOwnerRigidBody()->IsGround())
		{
			CPlayer* Player = GetCurPlayer();

			GetOwnerRigidBody()->Jump();
			Player->SetJumpStartYPos(Player->GetPos().y);
			Player->SetJumpingState(true);
			Player->PlusJumpCount();

			GetFSM()->ChangeState(L"Jump");
		}
		else
		{
			GetFSM()->ChangeState(L"Run");
		}
	}

	if(GetOwnerAnimator() != nullptr)
	{
		Vec2D ColPos = GetOwnerAnimator()->GetCurAnim()->GetColliderPos();
		Vec2D ColSize = GetOwnerAnimator()->GetCurAnim()->GetColliderSize();
		GetOwnerCollider()->SetOffsetPos(Vec2D(ColPos.x, ColPos.y - (GetObj()->GetScale().y / 2.f)));
		GetOwnerCollider()->SetScale(GetOwnerAnimator()->GetCurAnim()->GetColliderSize());
	}
}

void CSlideState::Exit()
{
	
}


