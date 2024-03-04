#pragma once
#include "CObject.h"

class CCollider;
class CAnimator;

class CPlayer :
    public CObject
{
private:
    CCollider*  m_Collider;
    CTexture*   m_PlayerImg;
    CAnimator*  m_Animator;

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

