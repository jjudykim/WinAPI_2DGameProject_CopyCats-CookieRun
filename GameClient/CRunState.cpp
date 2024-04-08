#include "pch.h"
#include "CRunState.h"

#include "CObject.h"

#include "CPathMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CCollider.h"

CRunState::CRunState()
	: m_PlayingAnim(false)
{
	
}

CRunState::~CRunState()
{
}


void CRunState::Set()
{
	CPlayerState::Set();

	wstring strFilePath = L"animation\\";
	strFilePath += GetCurPlayer()->GetCurCookie()._nameStr;
	strFilePath += L"\\" + GetCurPlayer()->GetCurCookie()._nameStr;

	GetOwnerAnimator()->LoadAnimation(L"Run", strFilePath + L"_Run.anim");
	GetOwnerAnimator()->LoadAnimation(L"UpFromSlide", strFilePath + L"_UpFromSlide.anim");
	GetOwnerRigidBody()->SetUseGravity(true);
}

void CRunState::Enter()
{
	CPlayerState::Enter();
	LOG(LOG_TYPE::DBG_WARNING, L"Run State ÁøÀÔ");
	if (GetFSM()->FindState(L"Slide") == GetFSM()->GetPrevState()
		|| GetFSM()->FindState(L"DoubleJump") == GetFSM()->GetPrevState())
	{ 
		GetOwnerAnimator()->Play(L"UpFromSlide", false); 
	}
	else
	{
		GetOwnerAnimator()->Play(L"Run", true);
	}
}

void CRunState::FinalTick()
{
	if (GetOwnerAnimator() != nullptr)
	{
		if (GetOwnerAnimator()->GetCurAnim()->IsFinish() && !m_PlayingAnim)
		{
			GetOwnerAnimator()->Play(L"Run", true);
			m_PlayingAnim = true;
		}
		Vec2D ColPos = GetOwnerAnimator()->GetCurAnim()->GetColliderPos();
		Vec2D ColSize = GetOwnerAnimator()->GetCurAnim()->GetColliderSize();
		GetOwnerCollider()->SetOffsetPos(Vec2D(ColPos.x, ColPos.y - (GetObj()->GetScale().y / 2.f)));
		GetOwnerCollider()->SetScale(GetOwnerAnimator()->GetCurAnim()->GetColliderSize());
	}
}

void CRunState::Exit()
{
	m_PlayingAnim = false;
}

