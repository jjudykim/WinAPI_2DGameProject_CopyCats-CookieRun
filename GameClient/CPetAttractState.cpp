#include "pch.h"
#include "CPetAttractState.h"

#include "CPet.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTimeMgr.h"


CPetAttractState::CPetAttractState()
{
}

CPetAttractState::~CPetAttractState()
{
}

void CPetAttractState::Set()
{
	CPetState::Set();

	wstring strFilePath = L"animation\\";
	strFilePath += L"Pet_" + GetCurPet()->GetCurPet()._nameStr;
	strFilePath += L"\\" + GetCurPet()->GetCurPet()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"PetAttract", strFilePath + L"_Attract.anim");
}

void CPetAttractState::Enter()
{
	CPetState::Enter();
	
	GetOwnerAnimator()->Play(L"PetAttract", true);

	GetOwnerCollider()->SetScale(Vec2D(80.f, 80.f));

	LOG(LOG_TYPE::DBG_LOG, L"Pet Attract ÁøÀÔ");
}

void CPetAttractState::FinalTick()
{
	Vec2D Destination = CCamera::GetInst()->GetRealPos(CEngine::GetInst()->GetResolution() / 2.f);

	float MoveDistanceX = (Destination.x - GetObj()->GetPos().x) * DT * 2.f;
	float MoveDistanceY = (Destination.y - GetObj()->GetPos().y) * DT * 2.f;

	GetObj()->SetPos(GetObj()->GetPos().x + MoveDistanceX, GetObj()->GetPos().y + MoveDistanceY);
}

void CPetAttractState::Exit()
{
	GetOwnerCollider()->SetOffsetPos(0);
	GetOwnerCollider()->SetScale(0);
}


