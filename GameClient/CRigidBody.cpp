#include "pch.h"
#include "CRigidBody.h"

#include "CObject.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	: m_UseGravity(false)
	, m_MaxJumpHeight(100.f)
	, m_WalkSpeed(0.f)
	, m_JumpSpeed(1000.f)
	, m_GravityAccel(3000.f)
	, m_Ground(true)
	, m_GroundInst(nullptr)
	, m_GroundDelegate(nullptr)
	//, m_AirInst(nullptr)
	//, m_AirDelegate(nullptr)
	// m_AirInst, m_AirDelegate을 nullptr로 초기화 시 힙 손상 발생하는 이유?
{
	
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::Walk(Vec2D& _originPos)
{
	_originPos += Vec2D(1.0f, 0.0f) * (m_WalkSpeed * DT);
}

void CRigidBody::Jump()
{
	m_VelocityByGravity = Vec2D(0.f, -1.f) * m_JumpSpeed;
	SetGround(false);
	LOG(LOG_TYPE::DBG_LOG, L"SetGround -> false");
}

void CRigidBody::finaltick()
{
	m_WalkSpeed = GetOwner()->GetSpeed();
	Vec2D vObjPos = GetOwner()->GetPos();

	Walk(vObjPos);

	if (!m_Ground)
	{
		Vec2D vJumpSpeed = Vec2D(0.f, 1.0f) * m_GravityAccel * DT;
		m_VelocityByGravity += vJumpSpeed;
		vObjPos += m_VelocityByGravity * DT;
	}
	else
	{
		GetOwner()->SetPos(Vec2D(vObjPos.x, 465.f));
		return;
	}
	GetOwner()->SetPos(vObjPos);
	DrawDebugLine(PEN_TYPE::PEN_BLUE, GetOwner()->GetRenderPos(), GetOwner()->GetRenderPos() + m_VelocityByGravity, 0.f);
}


