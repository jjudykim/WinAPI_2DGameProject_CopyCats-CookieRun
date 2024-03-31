#include "pch.h"
#include "CRunState.h"

#include "CObject.h"

#include "CPathMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

CRunState::CRunState()
	: m_PlayingAnim(false)
{
	
}

CRunState::~CRunState()
{
}


void CRunState::Set()
{
	CPlayerState::Set();

	wstring strFilePath = L"animation\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr;
	strFilePath += L"\\" + GetCurPlayer()->GetCurCookie()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"Run", strFilePath + L"_Run.anim");
	GetOwnerAnimator()->LoadAnimation(L"UpFromSlide", strFilePath + L"_UpFromSlide.anim");
	GetOwnerRigidBody()->SetUseGravity(true);
}

void CRunState::Enter()
{
	CPlayerState::Enter();

	if (GetFSM()->FindState(L"Slide") == GetFSM()->GetPrevState()) 
	{ 
		GetOwnerAnimator()->Play(L"UpFromSlide", false); 
	}
	else
	{
		GetOwnerAnimator()->Play(L"Run", true);
	}
}

void CRunState::FinalTick()
{
	if (GetOwnerAnimator() != nullptr)
	{
		if (GetOwnerAnimator()->GetCurAnim()->IsFinish() && !m_PlayingAnim)
		{
			GetOwnerAnimator()->Play(L"Run", true);
			m_PlayingAnim = true;
		}
	}
}

void CRunState::Exit()
{
	m_PlayingAnim = false;
}

