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
		Vec2D ColPos = m_pOwnerAnimator->GetCurAnim()->GetColliderPos();
		Vec2D ColSize = m_pOwnerAnimator->GetCurAnim()->GetColliderSize();

		if (m_pOwner->CheckCookieState(COOKIE_COMPLEX_STATE::GIANT))
		{
			m_pOwnerCollider->SetOffsetPos(Vec2D(ColPos.x * 2, ColPos.y - (GetObj()->GetScale().y / 3.f)));
			m_pOwnerCollider->SetScale(GetOwnerAnimator()->GetCurAnim()->GetColliderSize() * 2.f);
		}
		else
		{
			m_pOwnerCollider->SetOffsetPos(Vec2D(ColPos.x, ColPos.y - (GetObj()->GetScale().y / 2.f)));
			m_pOwnerCollider->SetScale(GetOwnerAnimator()->GetCurAnim()->GetColliderSize());
		}
		
	}
}

void CPlayerState::Exit()
{
}


