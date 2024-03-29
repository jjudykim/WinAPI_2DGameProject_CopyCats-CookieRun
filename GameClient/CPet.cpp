#include "pch.h"
#include "CPet.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CFSM.h"
#include "CAnimator.h"
#include "CAnimation.h"

// Pet State
#include "CPetRunState.h"

CPet::CPet()
	: m_Animator(nullptr)
	, m_RigidBody(nullptr)
	, m_FSM(nullptr)
	, m_ChaseSpeed(400)
{
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	CResourceMgr::GetInst()->LoadPetInfo();
}

CPet::~CPet()
{
}

void CPet::begin()
{
	m_FSM->AddState(L"Run", new CPetRunState);

	CObject* pPlayer = GET_CUR_LEVEL->FindObjectByName(L"Player");
	m_FSM->SetBlackboardData(L"Speed", DATA_TYPE::FLOAT, &m_ChaseSpeed);
	m_FSM->SetBlackboardData(L"Cookie", DATA_TYPE::OBJECT, pPlayer);
	m_FSM->SetState();

	m_FSM->ChangeState(L"Run");
}

void CPet::tick()
{
	CObject::tick();
}


