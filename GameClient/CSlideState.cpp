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

	GetOwnerRigidBody()->SetUseGravity(true);

	GetOwnerAnimator()->Play(L"Slide", true);
}

void CSlideState::FinalTick()
{
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


