#include "pch.h"
#include "CPlayerState.h"

#include "CObject.h"
#include "CPlayer.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CGameDataMgr.h"

CPlayerState::CPlayerState()
{
}

CPlayerState::~CPlayerState()
{
}


void CPlayerState::Set()
{
	m_pOwner = dynamic_cast<CPlayer*>(GetObj());
	m_pOwnerAnimator = GetObj()->GetComponent<CAnimator>();
	m_pOwnerRigidBody = GetObj()->GetComponent<CRigidBody>();
	m_pOwnerCollider = GetObj()->GetComponent<CCollider>();
}

void CPlayerState::Enter()
{
}

void CPlayerState::FinalTick()
{
	if (CGameDataMgr::GetInst()->IsCookieDead() == true)
	{
		if (GetFSM()->GetCurState() != GetFSM()->FindState(L"DeadByObs"))
		{
			GetFSM()->ChangeState(L"DeadByLife");
		}
	}

	if (GetOwnerAnimator() != nullptr)
	{
		Vec2D ColPos = GetOwnerAnimator()->GetCurAnim()->GetColliderPos();
		Vec2D ColSize = GetOwnerAnimator()->GetCurAnim()->GetColliderSize();

		if (GetCurPlayer()->CheckCookieState(COOKIE_COMPLEX_STATE::GIANT))
		{
			GetOwnerCollider()->SetOffsetPos(Vec2D(ColPos.x * 2, ColPos.y - (GetObj()->GetScale().y / 3.f)));
			GetOwnerCollider()->SetScale(GetOwnerAnimator()->GetCurAnim()->GetColliderSize() * 2.f);
		}
		else
		{
			GetOwnerCollider()->SetOffsetPos(Vec2D(ColPos.x, ColPos.y - (GetObj()->GetScale().y / 2.f)));
			GetOwnerCollider()->SetScale(GetOwnerAnimator()->GetCurAnim()->GetColliderSize());
		}
		
	}
}

void CPlayerState::Exit()
{
}


