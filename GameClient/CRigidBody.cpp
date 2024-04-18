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
	, m_Descending(false)
	, m_Ground(true)
	, m_GroundInst(nullptr)
	, m_GroundDelegate(nullptr)
	, m_GroundStandardPosY(COOKIE_DEFAULT_POSY)
	, m_Loaded(false)
{
	
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::Walk(Vec2D& _originPos, float _dt)
{
	_originPos += Vec2D(1.0f, 0.0f) * (m_WalkSpeed * _dt);
}

void CRigidBody::Jump()
{
	if (m_Giant == true) { m_JumpSpeed = 800.f; }
	else { m_JumpSpeed = 1000.f; }

	m_Ground = false;
	m_Descending = false;
	m_VelocityByJump = Vec2D(0.f, -1.f) * m_JumpSpeed;
}

void CRigidBody::finaltick()
{
	float dt = DT;

	// 만약 로딩 후 첫 틱이라면
	if (m_Loaded == false) { dt = 0.f; }

	m_WalkSpeed = GetOwner()->GetSpeed();
	Vec2D vObjPos = GetOwner()->GetPos();
	
	Walk(vObjPos, dt);
	if (m_UseGravity == true)
	{
		if (!m_Ground)
		{
			Vec2D vGravitySpeed = Vec2D(0.f, 1.0f) * m_GravityAccel * dt;
			if (m_Descending && vGravitySpeed.y >= 30)
			{
 				vGravitySpeed.y = 30;
			}
			m_VelocityByJump += vGravitySpeed;
			if (m_VelocityByJump.y > 0) m_Descending = true;
			vObjPos += m_VelocityByJump * dt;
		}
		else if (m_Ground && m_Descending)
		{
			vObjPos = Vec2D(vObjPos.x, m_GroundStandardPosY);
 			m_VelocityByJump = Vec2D(0.f, 0.f);
			m_Descending = false;
		}
	}
	GetOwner()->SetPos(vObjPos);
	if (m_Loaded == false) { m_Loaded = true; }
	DrawDebugLine(PEN_TYPE::PEN_BLUE, GetOwner()->GetRenderPos(), GetOwner()->GetRenderPos() + m_VelocityByJump, 0.f);
}


