#include "pch.h"
#include "CCollider.h"

#include "CObject.h"

#include "CLevelMgr.h"
#include "CLevel.h"

CCollider::CCollider()
	: m_OverlapCount(0)
	, m_OffsetPos(Vec2D())
{

}

CCollider::~CCollider()
{
}

void CCollider::finaltick()
{
	m_FinalPos = GetOwner()->GetPos() + m_OffsetPos;

	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	pLevel->RegisterCollider(this);

	if (m_OverlapCount != 0)
	{
		DrawDebugRect(PEN_TYPE::PEN_RED, m_FinalPos, m_Scale, 0.f);
	}
	else
	{
		DrawDebugRect(PEN_TYPE::PEN_GREEN, m_FinalPos, m_Scale, 0.f);
	}
}

void CCollider::BeginOverlap(CCollider* _OtherCollider)
{
}

void CCollider::OnOverlap(CCollider* _OtherCollider)
{
}

void CCollider::EndOverlap(CCollider* _OtherCollider)
{
}



