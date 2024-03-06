#pragma once
#include "CObject.h"

class CCollider;
class CAnimator;
class CRigidBody;

class CPlayer :
    public CObject
{
private:

    CCollider*  m_Collider;
    CTexture*   m_PlayerImg;
    CAnimator*  m_Animator;
    CRigidBody* m_RigidBody;

public:
    virtual void begin();
    virtual void tick();

    void BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    void OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    void EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;

public:
    virtual CObject* Clone() override { return new CPlayer(*this); }

public:
    CPlayer();
    ~CPlayer();
};

