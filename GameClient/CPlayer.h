#pragma once
#include "CObject.h"

#include "CFSM.h"

class CPlayer :
    public CObject
{
private:
    int     m_DoubleJumpCount;
    int     m_CurJumpCount;
    int     m_OverlapPLTCount;
    float   m_PrevYPos;
    float   m_JumpStartYPos;
    bool    m_Jumping;

    Vec2D   m_DefaultScale;
    Vec2D   m_ColliderDefualtScale;

    // Component
    CCollider*          m_Collider;
    CAnimator*          m_Animator;
    CRigidBody*         m_RigidBody;
    CFSM*               m_FSM;

    CookieInfo          m_CurCookie;
    int                 m_State;

public:
    virtual void begin();
    virtual void tick();
    virtual void render();

    void BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    void OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    void EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;

private:
    void GroundLogic()
    { 
        m_CurJumpCount = 0;
        m_Jumping = false;
    }

public:
    
    bool IsJumping() { return m_Jumping; }
    float GetJumpStartYPos() { return m_JumpStartYPos; }
    void SetJumpStartYPos(float _PosY) { m_JumpStartYPos = _PosY; }
    int GetCurJumpCount() { return m_CurJumpCount; }
    Vec2D GetDefaultScale() { return m_DefaultScale; }
    Vec2D GetColliderDefaultScale() { return m_ColliderDefualtScale; }

    void SetJumpingState(bool _Jumping) { m_Jumping = _Jumping; }
    void PlusJumpCount() { ++m_CurJumpCount; }
    void SetCurCookie(wstring _cookieStr) { m_CurCookie = CResourceMgr::GetInst()->FindCookieInfo(_cookieStr); }
    bool CheckCookieFSMState(const wstring& _str) { return m_FSM->GetCurState() == m_FSM->FindState(_str); }
    void ChangeCookieFSMState(const wstring& _str) { m_FSM->ChangeState(_str); }
    bool CheckCookieState(COOKIE_COMPLEX_STATE _State) { return m_State & (int)_State; }
    void TurnOnCookieState(COOKIE_COMPLEX_STATE _State) { m_State |= (int)_State; }
    void TurnOffCookieState(COOKIE_COMPLEX_STATE _State) { m_State &= ~(int)_State; }
    const CookieInfo& GetCurCookie() { return m_CurCookie; }

public:
    CLONE_DISABLE(CPlayer)

public:
    CPlayer();
    ~CPlayer();
};

