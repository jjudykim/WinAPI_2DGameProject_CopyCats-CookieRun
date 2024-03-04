#pragma once
#include "CComponent.h"

class CRigidBody :
    public CComponent
{
private:
    float   m_Mass;
    Vec2D   m_Force;

    Vec2D   m_Velocity;
    Vec2D   m_VelocityByGravity;
    Vec2D   m_AddVelocity;

    float m_MaxGravitySpeed;
    float m_GravityAccel;

    float   m_JumpSpeed;
    bool    m_Ground;

public:
    void AddForce(Vec2D _vForce) { m_Force += _vForce; }

    void SetMass(float _Mass) { m_Mass = _Mass; }
    void SetMaxGravitySpeed(float _Speed) { m_MaxGravitySpeed = _Speed; }
    void SetGravityVelocity(Vec2D _Velocity) { m_VelocityByGravity = _Velocity; }
    void SetJumpSpeed(float _Speed) { m_JumpSpeed = _Speed; }

    void Jump();

    float GetMass() { return m_Mass; }
    Vec2D GetGraivtyVelocity() { return m_VelocityByGravity; }

    void SetGround(bool _Ground)
    {
        if (m_Ground == _Ground)
            return;

        m_Ground = _Ground;

        if (m_Ground)
        {
            m_VelocityByGravity = Vec2D(0.f, 0.f);
        }
    }
public:
    virtual void finaltick() override;
    CLONE(CRigidBody);

public:
    CRigidBody();
    ~CRigidBody();
};

