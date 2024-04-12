#include "pch.h"
#include "CPlayer.h"

#include "CEngine.h"
#include "CObject.h"
#include "CPlatform.h"

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
	, m_Jumping(false)
	, m_JumpStartYPos(0.f)
	, m_PrevYPos(0.f)
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
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&CPlayer::GroundLogic);
	m_RigidBody->SetUseGravity(true);

	// FSM State Setting
	m_FSM->AddState(L"Run", new CRunState);
	m_FSM->AddState(L"Jump", new CJumpState);
	m_FSM->AddState(L"DoubleJump", new CDoubleJumpState);
	m_FSM->AddState(L"Slide", new CSlideState);
	m_FSM->AddState(L"Damage", new CDamageState);
	m_FSM->SetState();


	m_FSM->ChangeState(L"Run");

	// Sound Setting
	//CSound* pSound = CResourceMgr::GetInst()->LoadSound(L"Effect_CharJump", L"sound\\Effect_CharJump.wav");
	//pSound = CResourceMgr::GetInst()->LoadSound(L"Effect_CharSlide", L"sound\\Effect_CharSilde.wav");
}

void CPlayer::tick()
{
	CObject::tick();

	m_PrevYPos = GetPos().y;
}

void CPlayer::render()
{
	m_Animator->render(0.f);
}

void CPlayer::BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
	if (!CheckCookieState(COOKIE_COMPLEX_STATE::INVINCIBLE))
	{
		if (_OtherObj->GetLayerType() == LAYER_TYPE::OBSTACLE)
		{
			TurnOnCookieState(COOKIE_COMPLEX_STATE::INVINCIBLE);
			m_FSM->ChangeState(L"Damage");
		}
	}

	if (_OtherObj->GetLayerType() == LAYER_TYPE::PLATFORM)
	{
		++m_OverlapPLTCount;
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
				m_RigidBody->SetGround(true);
				//LOG(LOG_TYPE::DBG_LOG, L"SetGround -> true");
			}
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
			m_RigidBody->SetGround(false);
			m_RigidBody->SetGroundStandardPosY(COOKIE_DEFAULT_POSY);
			m_OverlapPLTCount = 0;
		}
	}
}
