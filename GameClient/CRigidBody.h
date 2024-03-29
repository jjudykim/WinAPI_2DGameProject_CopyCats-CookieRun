#pragma once
#include "CComponent.h"

typedef void(CObject::*DELEGATE)(void);

class CObject;

class CRigidBody :
    public CComponent
{
private:
    Vec2D   m_Force;
    float   m_MaxJumpHeight;

    Vec2D   m_Velocity;
    Vec2D   m_VelocityByGravity;
    Vec2D   m_AddVelocity;

    float   m_WalkSpeed;

    float   m_GravityAccel;
    bool    m_UseGravity;
    float   m_JumpSpeed;
    bool    m_Ground;

private:
    CObject*    m_GroundInst;
    DELEGATE    m_GroundDelegate;

    CObject*    m_AirInst;
    DELEGATE    m_AirDelegate;


public:
    void AddForce(Vec2D _vForce) { m_Force += _vForce; }
    void SetUseGravity(bool _use) { m_UseGravity = _use; }
    void SetGravityVelocity(Vec2D _Velocity) { m_VelocityByGravity = _Velocity; }
    void SetJumpSpeed(float _Speed) { m_JumpSpeed = _Speed; }

    void Walk(Vec2D& _OriginPos);
    void Jump();

    bool GetUseGravity() { return m_UseGravity; }
    Vec2D GetGraivtyVelocity() { return m_VelocityByGravity; }

    void SetGroundDelegate(CObject* _Inst, DELEGATE _MemFunc)
    {
        m_GroundInst = _Inst;
        m_GroundDelegate = _MemFunc;
    }

    void SetAirDelegate(CObject* _Inst, DELEGATE _MemFunc)
    {
        m_AirInst = _Inst;
        m_AirDelegate = _MemFunc;
    }


    void SetGround(bool _Ground)
    {
        if (m_Ground == _Ground)
            return;

        m_Ground = _Ground;

        if (m_Ground)
        {
            m_VelocityByGravity = Vec2D(0.f, 0.f);
            if (m_GroundInst && m_GroundDelegate)
                (m_GroundInst->*m_GroundDelegate)();
        }
        else
        {
            /*if (m_AirInst && m_AirDelegate)
                (m_AirInst->*m_AirDelegate)();*/
        }
    }

public:
    virtual void finaltick() override;

    CLONE(CRigidBody);

public:
    CRigidBody();
    ~CRigidBody();
};

