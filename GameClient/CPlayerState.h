#pragma once
#include "CState.h"

class CAnimator;

class CPlayerState :
    public CState
{
    CookieInfo            m_CurCookie;
    CAnimator*            m_OwnerAnimator;
    wstring               m_AnimPath;
    Vec2D                 m_PlayerScale;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    void SetCookieInfo(CookieInfo& _info) { m_CurCookie = _info; }
    void SetOwnerAnimator(CAnimator* _animator) { m_OwnerAnimator = _animator; }

    CookieInfo GetCurCookie() { return m_CurCookie; }
    CAnimator* GetOwnerAnimator() { return m_OwnerAnimator; }

public:
    CPlayerState();
    ~CPlayerState();
};

