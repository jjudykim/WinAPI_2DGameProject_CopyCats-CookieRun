#include "pch.h"
#include "CPetState.h"

#include "CPet.h"
#include "CAnimator.h"
#include "CCollider.h"

CPetState::CPetState()
	: m_pOwner(nullptr)
	, m_pOwnerAnimator(nullptr)
	, m_pOwnerCollider(nullptr)
{
}

CPetState::~CPetState()
{
}

void CPetState::Set()
{
	m_pOwner = dynamic_cast<CPet*>(GetObj());
	m_pOwnerAnimator = GetObj()->GetComponent<CAnimator>();
	m_pOwnerCollider = GetObj()->GetComponent<CCollider>();
}

void CPetState::Enter()
{
}

void CPetState::FinalTick()
{
}

void CPetState::Exit()
{
}


