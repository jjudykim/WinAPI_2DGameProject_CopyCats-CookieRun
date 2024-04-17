#include "pch.h"
#include "CSlideState.h"

#include "CKeyMgr.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CSound.h"

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
	SetSoundEffect(CResourceMgr::GetInst()->FindSound(L"Effect_CharSlide"));
}

void CSlideState::Enter()
{
	CPlayerState::Enter();
	LOG(LOG_TYPE::DBG_WARNING, L"Slide State ÁøÀÔ");
	GetOwnerRigidBody()->SetUseGravity(true);
	GetOwnerAnimator()->Play(L"Slide", true);

	GetSoundEffect()->SetVolume(80.f);
	GetSoundEffect()->Play();
}

void CSlideState::FinalTick()
{
	CPlayerState::FinalTick();

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
}

void CSlideState::Exit()
{
	
}


