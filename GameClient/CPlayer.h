#pragma once
#include "CObject.h"

#include "CFSM.h"

class CPlayer :
    public CObject
{
private:
    int m_DoubleJumpCount;
    int m_CurJumpCount;

    // Component
    CCollider*   m_Collider;
    CAnimator*   m_Animator;
    CRigidBody*  m_RigidBody;
    CFSM*        m_FSM;

    
    CookieInfo   m_CurCookie;
    COOKIE_STATE m_State;

public:
    virtual void begin();
    virtual void tick();

    void BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    void OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    void EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;

private:
    void RestoreJumpCount() { m_CurJumpCount = 0; }

public:
    void SetCurCookie(COOKIE_TYPE _cookieType) { m_CurCookie._type = _cookieType; }
    CookieInfo GetCurCookie() { return m_CurCookie; }
public:
    CLONE_DISABLE(CPlayer)

public:
    CPlayer();
    ~CPlayer();
};

