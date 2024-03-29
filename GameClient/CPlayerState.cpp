#include "pch.h"
#include "CPlayerState.h"

#include "CObject.h"
#include "CPlayer.h"

#include "CCollider.h"
#include "CAnimation.h"
#include "CAnimator.h"

CPlayerState::CPlayerState()
{
}

CPlayerState::~CPlayerState()
{
}


void CPlayerState::Set()
{
	m_pOwner = dynamic_cast<CPlayer*>(GetObj());
	m_pOwnerAnimator = GetObj()->GetComponent<CAnimator>();
	m_pOwnerCollider = GetObj()->GetComponent<CCollider>();
}

void CPlayerState::Enter()
{

}

void CPlayerState::FinalTick()
{
}

void CPlayerState::Exit()
{
}


