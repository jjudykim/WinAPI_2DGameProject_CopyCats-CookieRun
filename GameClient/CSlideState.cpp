#include "pch.h"
#include "CSlideState.h"

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

	// TODO : stage 구성 후 true로 변경하기
	GetOwnerRigidBody()->SetUseGravity(false);

	GetOwnerAnimator()->Play(L"Slide", true);
}

void CSlideState::FinalTick()
{
	if(GetOwnerAnimator() != nullptr)
	{
		GetOwnerCollider()->SetOffsetPos(GetOwnerAnimator()->GetCurAnim()->GetColliderPos());
		GetOwnerCollider()->SetScale(GetOwnerAnimator()->GetCurAnim()->GetColliderSize());
	}
}

void CSlideState::Exit()
{
	
}


