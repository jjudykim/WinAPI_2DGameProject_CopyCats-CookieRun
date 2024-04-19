#include "pch.h"
#include "CPetDashState.h"

#include "CPet.h"
#include "CAnimator.h"
#include "CTimeMgr.h"

CPetDashState::CPetDashState()
{
}

CPetDashState::~CPetDashState()
{
}

void CPetDashState::Set()
{
	CPetState::Set();

	wstring strFilePath = L"animation\\";
	strFilePath += L"Pet_" + GetCurPet()->GetCurPet()._nameStr;
	strFilePath += L"\\" + GetCurPet()->GetCurPet()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"PetDash", strFilePath + L"_Dash.anim");
}

void CPetDashState::Enter()
{
	CPetState::Enter();

	GetOwnerAnimator()->Play(L"PetDash", true);

	LOG(LOG_TYPE::DBG_LOG, L"Pet Dash ¡¯¿‘");
}

void CPetDashState::FinalTick()
{
	float Speed = GetBlackboardData<float>(L"Speed");
	CObject* pCookie = GetBlackboardData<CObject*>(L"Cookie");

	float ChaseYPos = pCookie->GetPos().y - (pCookie->GetScale().y / 2.f);
	Vec2D Diff = (0, ChaseYPos - GetObj()->GetPos().y);
	if (abs(Diff.y) > 5.f)
	{
		Speed = abs(Diff.y) / 0.3f;
		Diff.Normalize();
		Vec2D vPos = Vec2D(GetObj()->GetPos().x, GetObj()->GetPos().y + Diff.y * Speed * DT);
		GetObj()->SetPos(vPos);
	}
}

void CPetDashState::Exit()
{
}


