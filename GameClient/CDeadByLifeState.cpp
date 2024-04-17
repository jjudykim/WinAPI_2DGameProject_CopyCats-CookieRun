#include "pch.h"
#include "CDeadByLifeState.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CSound.h"

CDeadByLifeState::CDeadByLifeState()
{
}

CDeadByLifeState::~CDeadByLifeState()
{
}


void CDeadByLifeState::Set()
{
	CPlayerState::Set();

	wstring strFilePath = L"animation\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr + L"\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"DeadByLife", strFilePath + L"_DeadByLife.anim");
	SetSoundEffect(CResourceMgr::GetInst()->FindSound(L"Effect_GameEnd"));
}

void CDeadByLifeState::Enter()
{
	GetOwnerAnimator()->Play(L"DeadByLife", false);
	GetSoundEffect()->SetVolume(70.f);
	GetSoundEffect()->Play();
}

void CDeadByLifeState::FinalTick()
{
	if (GetOwnerAnimator() != nullptr)
	{
		Vec2D ColPos = GetOwnerAnimator()->GetCurAnim()->GetColliderPos();
		Vec2D ColSize = GetOwnerAnimator()->GetCurAnim()->GetColliderSize();
		GetOwnerCollider()->SetOffsetPos(Vec2D(ColPos.x, ColPos.y - (GetObj()->GetScale().y / 2.f)));
		GetOwnerCollider()->SetScale(GetOwnerAnimator()->GetCurAnim()->GetColliderSize());
	}
}

void CDeadByLifeState::Exit()
{
}

