#include "pch.h"
#include "CPlayer.h"

#include "CEngine.h"
#include "CObject.h"

#include "CLevelMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CFSM.h"
#include "CAnimator.h"
#include "CAnimation.h"

// State header
#include "CRunState.h"
#include "CJumpState.h"
#include "CSlideState.h"
#include "CDamageState.h"
#include "CInvState.h"

CPlayer::CPlayer()
	: m_DoubleJumpCount(2)
	, m_CurJumpCount(0)
	, m_State(COOKIE_STATE::NONE)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	m_Collider->SetName(L"Cookie's Collider");
	m_Collider->SetOffsetPos(Vec2D(13.5f, 70.f));
	m_Collider->SetScale(Vec2D(70.f, 135.f));

	// FSM State Setting
	m_FSM->AddState(L"Run", new CRunState);
	//m_FSM->AddState(L"Jump", new CJumpState);

	CResourceMgr::GetInst()->LoadCookieInfo();
}

CPlayer::~CPlayer()
{
}


void CPlayer::begin()
{
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&CPlayer::RestoreJumpCount);
	m_FSM->ChangeState(L"Run");
}

void CPlayer::tick()
{
	CObject::tick();

	if (CKeyMgr::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
	{
		if (m_DoubleJumpCount > m_CurJumpCount)
		{
			m_RigidBody->Jump();
			m_CurJumpCount += 1;
		}
	}
}

void CPlayer::BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlayer::OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlayer::EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
}
