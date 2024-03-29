#include "pch.h"
#include "CPetState.h"

#include "CPet.h"
#include "CAnimator.h"

CPetState::CPetState()
{
}

CPetState::~CPetState()
{
}

void CPetState::Set()
{
	m_pOwner = dynamic_cast<CPet*>(GetObj());
	m_pOwnerAnimator = GetObj()->GetComponent<CAnimator>();
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


