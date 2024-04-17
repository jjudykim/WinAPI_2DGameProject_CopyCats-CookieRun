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
    Vec2D   m_VelocityByJump;
    bool    m_Descending;

    float   m_WalkSpeed;

    float   m_GravityAccel;
    bool    m_UseGravity;
    float   m_JumpSpeed;
    bool    m_Ground;
    float   m_GroundStandardPosY;
    bool    m_Giant;

    bool    m_Loaded;    

private:
    CObject*    m_GroundInst;
    DELEGATE    m_GroundDelegate;

public:
    void AddForce(Vec2D _vForce) { m_Force += _vForce; }
    void SetUseGravity(bool _use) { m_UseGravity = _use; }
    void SetGravityVelocity(Vec2D _Velocity) { m_VelocityByJump = _Velocity; }
    void SetJumpSpeed(float _Speed) { m_JumpSpeed = _Speed; }
    void SetGroundStandardPosY(float _PosY) { m_GroundStandardPosY = _PosY; }
    void SetGiant(bool _Giant) { m_Giant = _Giant; }

    void Walk(Vec2D& _OriginPos, float _dt);
    void Jump();

    bool GetUseGravity() { return m_UseGravity; }
    bool IsDescending() { return m_Descending; }
    bool IsGround() { return m_Ground; }
    Vec2D GetGraivtyVelocity() { return m_VelocityByJump; }

    void SetGroundDelegate(CObject* _Inst, DELEGATE _MemFunc)
    {
        m_GroundInst = _Inst;
        m_GroundDelegate = _MemFunc;
    }

    void SetGround(bool _Ground)
    {
        if (m_Ground == _Ground)
            return;

        m_Ground = _Ground;

        if (m_Ground)
        {
            m_VelocityByJump = Vec2D(0.f, 0.f);
            if (m_GroundInst && m_GroundDelegate)
                (m_GroundInst->*m_GroundDelegate)();
        }
    }

public:
    virtual void finaltick() override;

    CLONE(CRigidBody);

public:
    CRigidBody();
    ~CRigidBody();
};

