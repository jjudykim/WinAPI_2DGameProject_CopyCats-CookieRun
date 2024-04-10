#include "pch.h"
#include "CDamageState.h"

#include "CTimeMgr.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"

CDamageState::CDamageState()
	: m_Timer(0.f)
{
}

CDamageState::~CDamageState()
{
}

void CDamageState::Set()
{
	CPlayerState::Set();
	
	wstring strFilePath = L"animation\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr + L"\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"Damage", strFilePath + L"_Damage.anim");

	m_Timer = 0.f;
}

void CDamageState::Enter()
{
	m_Timer = 0.f;
	GetOwnerAnimator()->Play(L"Damage", false);
	GetOwnerRigidBody()->SetUseGravity(true);
}

void CDamageState::FinalTick()
{
	m_Timer += DT;
	if (m_Timer >= 0.3f)
	{
		GetFSM()->ChangeState(L"Run");
	}
}

void CDamageState::Exit()
{
}

