#include "pch.h"
#include "CPlayer.h"

#include "CEngine.h"
#include "CObject.h"
#include "CPlatform.h"

#include "CLevelMgr.h"
#include "CGameDataMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CObstacle.h"
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
#include "CDashState.h"
#include "CDeadByObsState.h"
#include "CDeadByLifeState.h"


CPlayer::CPlayer()
	: m_DoubleJumpCount(2)
	, m_CurJumpCount(0)
	, m_OverlapPLTCount(0)
	, m_Jumping(false)
	, m_JumpStartYPos(0.f)
	, m_PrevYPos(0.f)
	, m_DefaultScale(0.f)
	, m_ColliderDefualtScale(0.f)
	, m_State(0)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_FSM = (CFSM*)AddComponent(new CFSM);
}

CPlayer::~CPlayer()
{
}


void CPlayer::begin()
{
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&CPlayer::GroundLogic);
	m_RigidBody->SetUseGravity(true);

	// FSM State Setting
	m_FSM->AddState(L"Run", new CRunState);
	m_FSM->AddState(L"Jump", new CJumpState);
	m_FSM->AddState(L"DoubleJump", new CDoubleJumpState);
	m_FSM->AddState(L"Slide", new CSlideState);
	m_FSM->AddState(L"Damage", new CDamageState);
	m_FSM->AddState(L"Dash", new CDashState);
	m_FSM->AddState(L"DeadByObs", new CDeadByObsState);
	m_FSM->AddState(L"DeadByLife", new CDeadByLifeState);
	m_FSM->SetState();

	m_DefaultScale = GetScale();
	m_ColliderDefualtScale = m_Collider->GetScale();

	m_FSM->ChangeState(L"Run");
}

void CPlayer::tick()
{
	m_PrevYPos = GetPos().y;
	
	CObject::tick();
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
			if (!m_Jumping)
			{
				CPlatform* plt = static_cast<CPlatform*>(_OtherObj);

				if (0 < (int)(GetPos().y - m_PrevYPos))
				{
					if (plt->GetPLTType() == PLT_TYPE::FLOATED)
					{
						m_RigidBody->SetGroundStandardPosY(plt->GetPos().y + (plt->GetScale().y / 4.f));

					}
					else
					{
						m_RigidBody->SetGroundStandardPosY(COOKIE_DEFAULT_POSY);
					}
					m_RigidBody->SetGround(true);
				}
			}
		}
	}

	if (_OtherObj->GetLayerType() == LAYER_TYPE::OBSTACLE)
	{
		if (!((m_State & (UINT)COOKIE_COMPLEX_STATE::INVINCIBLE) || (m_State & (UINT)COOKIE_COMPLEX_STATE::GIANT) || (m_State & (UINT)COOKIE_COMPLEX_STATE::BOOST)))
		{
			CGameDataMgr::GetInst()->DeductHP(30);
			if (CGameDataMgr::GetInst()->IsCookieDead() == true) m_FSM->ChangeState(L"DeadByObs");
			else
			{
				TurnOnCookieState(COOKIE_COMPLEX_STATE::INVINCIBLE);
				m_FSM->ChangeState(L"Damage");
			}
		}
		else if (m_State & (UINT)COOKIE_COMPLEX_STATE::GIANT || m_State & (UINT)COOKIE_COMPLEX_STATE::BOOST)
		{
			CObstacle* obs = static_cast<CObstacle*>(_OtherObj);
			obs->SetCrash(true);
		}
	}
}

void CPlayer::OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) 
{
	if (_OtherObj->GetLayerType() == LAYER_TYPE::PLATFORM)
	{
		if (m_OverlapPLTCount > 0)
		{
			if (!m_Jumping)
			{
				CPlatform* plt = static_cast<CPlatform*>(_OtherObj);

				if (plt->GetPLTType() == PLT_TYPE::FLOATED)
				{
					if (0 < GetPos().y - m_PrevYPos)
					{
						m_RigidBody->SetGroundStandardPosY(plt->GetPos().y + (plt->GetScale().y / 4.f));
					}
				}
				else
				{
					m_RigidBody->SetGroundStandardPosY(COOKIE_DEFAULT_POSY);
				}
				m_RigidBody->SetGround(true);
			}
		}
	}
}

void CPlayer::EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetLayerType() == LAYER_TYPE::PLATFORM)
	{
		--m_OverlapPLTCount;
		CPlatform* plt = static_cast<CPlatform*>(_OtherObj);
		if (plt->GetPLTType() == PLT_TYPE::FLOATED)
		{
			m_RigidBody->SetGround(false);
			m_RigidBody->SetGroundStandardPosY(COOKIE_DEFAULT_POSY);
		}

		if (m_OverlapPLTCount <= 0)
		{
			m_RigidBody->SetGround(false);
			m_RigidBody->SetGroundStandardPosY(COOKIE_DEFAULT_POSY);
			m_OverlapPLTCount = 0;
		}
	}

	if (_OtherObj->GetLayerType() == LAYER_TYPE::JELLY)
	{
		--_OwnCollider->m_OverlapCount;
	}
}
