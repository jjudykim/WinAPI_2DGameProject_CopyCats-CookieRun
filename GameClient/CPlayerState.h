#pragma once
#include "CState.h"

#include "CPlayer.h"

class CAnimator;

class CPlayerState :
    public CState
{
    CPlayer*              m_pOwner;
    CAnimator*            m_pOwnerAnimator;
    CRigidBody*           m_pOwnerRigidBody;
    CCollider*            m_pOwnerCollider;
    wstring               m_AnimPath;

public:
    virtual void Set() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    void SetOwnerAnimator(CAnimator* _animator) { m_pOwnerAnimator = _animator; }
    void SetOwnerCollider(CCollider* _collider) { m_pOwnerCollider = _collider; }

    CPlayer* GetCurPlayer() { return m_pOwner; }
    CCollider* GetOwnerCollider() { return m_pOwnerCollider; }
    CAnimator* GetOwnerAnimator() { return m_pOwnerAnimator; }
    CRigidBody* GetOwnerRigidBody() { return m_pOwnerRigidBody; }

public:
    CPlayerState();
    ~CPlayerState();
};

