#pragma once
#include "CObject.h"

class CCollider;
class CAnimator;
class CRigidBody;

class CPlayer :
    public CObject
{
private:
    int m_DoubleJumpCount;
    int m_CurJumpCount;

    CCollider*  m_Collider;
    CAnimator*  m_Animator;
    CRigidBody* m_RigidBody;

public:
    virtual void begin();
    virtual void tick();

    void BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    void OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    void EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;

private:
    void RestoreJumpCount() { m_CurJumpCount = 0; }

public:
    CLONE_DISABLE(CPlayer)

public:
    CPlayer();
    ~CPlayer();
};

