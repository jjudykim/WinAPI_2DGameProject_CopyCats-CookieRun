#include "pch.h"
#include "CDeadByObsState.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CSound.h"

CDeadByObsState::CDeadByObsState()
{
}

CDeadByObsState::~CDeadByObsState()
{
}

void CDeadByObsState::Set()
{
	CPlayerState::Set();

	wstring strFilePath = L"animation\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr + L"\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"DeadByObs", strFilePath + L"_DeadByObs.anim");
	SetSoundEffect(CResourceMgr::GetInst()->FindSound(L"Effect_GameEnd"));
}

void CDeadByObsState::Enter()
{
	GetOwnerAnimator()->Play(L"DeadByObs", false);
	GetSoundEffect()->SetVolume(70.f);
	GetSoundEffect()->Play();
}

void CDeadByObsState::FinalTick()
{
	if (GetOwnerAnimator() != nullptr)
	{
		Vec2D ColPos = GetOwnerAnimator()->GetCurAnim()->GetColliderPos();
		Vec2D ColSize = GetOwnerAnimator()->GetCurAnim()->GetColliderSize();
		GetOwnerCollider()->SetOffsetPos(Vec2D(ColPos.x, ColPos.y - (GetObj()->GetScale().y / 2.f)));
		GetOwnerCollider()->SetScale(GetOwnerAnimator()->GetCurAnim()->GetColliderSize());
	}
}

void CDeadByObsState::Exit()
{
}


