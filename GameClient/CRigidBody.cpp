#include "pch.h"
#include "CRigidBody.h"

#include "CObject.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	: m_UseGravity(true)
	, m_MaxJumpHeight(100.f)
	, m_WalkSpeed(0.f)
	, m_JumpSpeed(1000.f)
	, m_GravityAccel(3000.f)
	, m_Ground(true)
	, m_GroundInst(nullptr)
	, m_GroundDelegate(nullptr)
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
	m_VelocityByJump = Vec2D(0.f, -1.f) * m_JumpSpeed;
}

void CRigidBody::finaltick()
{
	m_WalkSpeed = GetOwner()->GetSpeed();
	Vec2D vObjPos = GetOwner()->GetPos();

	Walk(vObjPos);
	if (m_UseGravity == true)
	{
		if (!m_Ground)
		{
			Vec2D vGravitySpeed = Vec2D(0.f, 1.0f) * m_GravityAccel * DT;
			m_VelocityByJump += vGravitySpeed;
			vObjPos += m_VelocityByJump * DT;
		}
		else
		{
			m_VelocityByJump = Vec2D(0.f, 0.f);
		}
	}
	GetOwner()->SetPos(vObjPos);
	DrawDebugLine(PEN_TYPE::PEN_BLUE, GetOwner()->GetRenderPos(), GetOwner()->GetRenderPos() + m_VelocityByJump, 0.f);
}


