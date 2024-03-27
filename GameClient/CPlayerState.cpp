#include "pch.h"
#include "CPlayerState.h"

#include "CObject.h"
#include "CPlayer.h"

#include "CAnimation.h"
#include "CAnimator.h"

CPlayerState::CPlayerState()
{
	
}

CPlayerState::~CPlayerState()
{
}


void CPlayerState::Enter()
{
	m_CurCookie = dynamic_cast<CPlayer*>(GetObj())->GetCurCookie();
	m_OwnerAnimator = GetObj()->GetComponent<CAnimator>();
}

void CPlayerState::FinalTick()
{
}

void CPlayerState::Exit()
{
}


