#include "pch.h"
#include "CRigidBody.h"

#include "CObject.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	: m_UseGravity(false)
	, m_JumpSpeed(600.f)
	, m_GravityAccel(1500.f)
	, m_Ground(false)
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
	m_VelocityByGravity += Vec2D(0.f, -1.f) * m_JumpSpeed;
	
	SetGround(false);
}

void CRigidBody::finaltick()
{
	m_WalkSpeed = GetOwner()->GetSpeed();
	Vec2D vObjPos = GetOwner()->GetPos();

	Walk(vObjPos);

	if (!m_Ground)
	{
		m_VelocityByGravity += Vec2D(0.f, 1.f) * m_GravityAccel * DT;
	}
	vObjPos += m_VelocityByGravity * DT;
	GetOwner()->SetPos(vObjPos);

	
	DrawDebugLine(PEN_TYPE::PEN_BLUE, GetOwner()->GetRenderPos(), GetOwner()->GetRenderPos() + m_VelocityByGravity, 0.f);
}


