#include "pch.h"
#include "CCollider.h"

#include "CObject.h"

#include "CLevelMgr.h"
#include "CLevel.h"

CCollider::CCollider()
	: m_OverlapCount(0)
	, m_OffsetPos(Vec2D(0))
	, m_CollidingCol(nullptr)
{

}

CCollider::CCollider(const CCollider& _Other)
	: CComponent(_Other)
	, m_OffsetPos(_Other.m_OffsetPos)
	, m_Scale(_Other.m_Scale)
	, m_OverlapCount(0)
	, m_CollidingCol(nullptr)
{
}

CCollider::~CCollider()
{
}

void CCollider::finaltick()
{
	m_FinalPos = GetOwner()->GetRenderPos() + m_OffsetPos;

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
	m_OverlapCount++;
	m_CollidingCol = _OtherCollider;
	GetOwner()->BeginOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}

void CCollider::OnOverlap(CCollider* _OtherCollider)
{
	m_CollidingCol = _OtherCollider;
	GetOwner()->OnOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}

void CCollider::EndOverlap(CCollider* _OtherCollider)
{
	m_OverlapCount--;
	if (m_OverlapCount == 0) m_CollidingCol = nullptr;
	GetOwner()->EndOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}



