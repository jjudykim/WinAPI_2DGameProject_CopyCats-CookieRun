#pragma once
#include "CState.h"

class CPet;
class CAnimator;

class CPetState :
    public CState
{
private:
    CPet*       m_pOwner;
    CAnimator*  m_pOwnerAnimator;

public:
    virtual void Set() override;
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void Exit() override;

public:
    void SetOwnerAnimator(CAnimator* _animator) { m_pOwnerAnimator = _animator; }

    CPet* GetCurPet() { return m_pOwner; }
    CAnimator* GetOwnerAnimator() { return m_pOwnerAnimator; }

public:
    CPetState();
    ~CPetState();
};

