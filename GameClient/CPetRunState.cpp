#include "pch.h"
#include "CPetRunState.h"

#include "CTimeMgr.h"
#include "CPet.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPetRunState::CPetRunState()
{
}

CPetRunState::~CPetRunState()
{
}

void CPetRunState::Set()
{
	CPetState::Set();

	wstring strFilePath = L"animation\\";
	strFilePath += L"Pet_" + GetCurPet()->GetCurPet()._nameStr;
	strFilePath += L"\\" + GetCurPet()->GetCurPet()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"PetRun", strFilePath + L"_Run.anim");
}

void CPetRunState::Enter()
{
	CPetState::Enter();

	GetOwnerAnimator()->Play(L"PetRun", true);

}

void CPetRunState::FinalTick()
{
	float Speed = GetBlackboardData<float>(L"Speed");
	CObject* pCookie = GetBlackboardData<CObject*>(L"Cookie");

	Vec2D Diff = (0, pCookie->GetPos().y - GetObj()->GetPos().y);
	if (abs(Diff.y) > 5.f)
	{
		Speed = abs(Diff.y) / 0.3f;
		Diff.Normalize();
		Vec2D vPos = Vec2D(GetObj()->GetPos().x, GetObj()->GetPos().y + Diff.y * Speed * DT);
		GetObj()->SetPos(vPos);
	}
}

void CPetRunState::Exit()
{
}


