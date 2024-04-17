#include "pch.h"
#include "CDamageState.h"

#include "CTimeMgr.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CSound.h"

CDamageState::CDamageState()
{
}

CDamageState::~CDamageState()
{
}

void CDamageState::Set()
{
	CPlayerState::Set();
	
	wstring strFilePath = L"animation\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr + L"\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"Damage", strFilePath + L"_Damage.anim");
	SetSoundEffect(CResourceMgr::GetInst()->FindSound(L"Effect_CharDamage"));
}

void CDamageState::Enter()
{
	GetOwnerAnimator()->Play(L"Damage", false);
	GetSoundEffect()->SetVolume(70.f);
	GetSoundEffect()->Play();
	CTimeMgr::GetInst()->AddTimer(0.3f, [this]() { GetFSM()->ChangeState(L"Run"); }, false);
}

void CDamageState::FinalTick()
{
	CPlayerState::FinalTick();
}

void CDamageState::Exit()
{
}

