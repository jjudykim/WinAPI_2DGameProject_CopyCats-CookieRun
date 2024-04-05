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
#include "CDoubleJumpState.h"
#include "CSlideState.h"
#include "CDamageState.h"
#include "CInvState.h"

CPlayer::CPlayer()
	: m_DoubleJumpCount(2)
	, m_CurJumpCount(0)
	, m_OverlapPLTCount(0)
	, m_State(COOKIE_STATE::NONE)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	CResourceMgr::GetInst()->LoadCookieInfo();
}

CPlayer::~CPlayer()
{
}


void CPlayer::begin()
{
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&CPlayer::RestoreJumpCount);

	// FSM State Setting
	m_FSM->AddState(L"Run", new CRunState);
	m_FSM->AddState(L"Jump", new CJumpState);
	m_FSM->AddState(L"DoubleJump", new CDoubleJumpState);
	m_FSM->AddState(L"Slide", new CSlideState);
	m_FSM->SetState();

	m_FSM->ChangeState(L"Run");
}

void CPlayer::tick()
{
	CObject::tick();

	if (CKeyMgr::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP 
		&& m_RigidBody->IsGround() == true)
	{
		m_JumpStartYPos = GetPos().y;
		if (m_DoubleJumpCount > m_CurJumpCount)
		{
			++m_CurJumpCount;
			if (m_CurJumpCount == 2)
			{
				m_FSM->ChangeState(L"DoubleJump");
			}
			else
			{
				m_FSM->ChangeState(L"Jump");
			}
			m_RigidBody->Jump();
		}
	}
	else if (KEY_TAP(KEY::DOWN) && m_RigidBody->IsGround())
	{
		m_FSM->ChangeState(L"Slide");
	}
	else if (KEY_RELEASED(KEY::DOWN))
	{
		m_FSM->ChangeState(L"Run");
	}
}

void CPlayer::render()
{
	m_Animator->render(0.f);
}

void CPlayer::BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetLayerType() == LAYER_TYPE::PLATFORM)
	{
		++m_OverlapPLTCount;
		if (m_OverlapPLTCount > 0)
		{
			m_RigidBody->SetGround(true);
			LOG(LOG_TYPE::DBG_LOG, L"SetGround -> true");
		}
		
	}
}

void CPlayer::OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlayer::EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetLayerType() == LAYER_TYPE::PLATFORM)
	{
		--m_OverlapPLTCount;
		if (m_OverlapPLTCount <= 0)
		{
			m_RigidBody->SetUseGravity(true);
			m_RigidBody->SetGround(false);
			m_OverlapPLTCount = 0;
			LOG(LOG_TYPE::DBG_LOG, L"SetGround -> false");
		}
	}
}
