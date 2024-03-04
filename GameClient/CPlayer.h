#pragma once
#include "CObject.h"

class CCollider;
class CAnimator;
class CRigidBody;

class CPlayer :
    public CObject
{
private:
    float m_Speed;

    CCollider*  m_Collider;
    CTexture*   m_PlayerImg;
    CAnimator*  m_Animator;
    CRigidBody* m_RigidBody;

public:
    virtual void begin();
    virtual void tick();
    virtual void render();

public:
    virtual CObject* Clone() override { return new CPlayer(*this); }

public:
    CPlayer();
    ~CPlayer();
};

