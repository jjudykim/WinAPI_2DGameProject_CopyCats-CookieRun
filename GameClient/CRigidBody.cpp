#include "pch.h"
#include "CRigidBody.h"

#include "CObject.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	: m_Mass(1.f)
	, m_JumpSpeed(400.f)
	, m_MaxGravitySpeed(0.f)
	, m_GravityAccel(980.f)
	, m_Ground(false)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::Jump()
{
	m_VelocityByGravity += Vec2D(0.f, -1.f) * m_JumpSpeed;
	SetGround(false);
}

void CRigidBody::finaltick()
{
	Vec2D vObjPos = GetOwner()->GetPos();
	Vec2D vAccel = m_Force / m_Mass;

	if (!m_Ground)
	{
		m_Velocity += vAccel * DT * 0.5f;
	}
	else
	{
		m_Velocity += vAccel * DT * 1.f;
	}

	if (m_Force.IsZero())
	{
		float Speed = m_Velocity.Length();

		if (Speed < 0)
			Speed = 0.f;

		if (!m_Velocity.IsZero())
			m_Velocity.Normalize();

		m_Velocity *= Speed;
	}

	if (!m_Ground)
	{
		m_VelocityByGravity += Vec2D(0.f, 1.f) * m_GravityAccel * DT;

		if (m_MaxGravitySpeed != 0.f && m_MaxGravitySpeed < m_VelocityByGravity.Length())
		{
			m_VelocityByGravity.Normalize();
			m_VelocityByGravity *= m_MaxGravitySpeed;
		}
	}

	Vec2D vFinalVelocity = m_Velocity + m_VelocityByGravity;

	vObjPos += vFinalVelocity * DT;
	GetOwner()->SetPos(vObjPos);

	m_Force = Vec2D(0.f, 0.f);
	m_AddVelocity = Vec2D(0.f, 0.f);

	DrawDebugLine(PEN_TYPE::PEN_BLUE, vObjPos, vObjPos + vFinalVelocity, 0.f);
}


