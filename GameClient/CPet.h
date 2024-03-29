#pragma once
#include "CObject.h"

class CPet :
    public CObject
{
private:
    CAnimator*      m_Animator;
    CRigidBody*     m_RigidBody;
    CFSM*           m_FSM;

    PetInfo         m_CurPet;
    
    float           m_ChaseSpeed;

public:
    virtual void begin();
    virtual void tick();

public:
    void SetCurPet(PET_TYPE _petType) { m_CurPet = CResourceMgr::GetInst()->FindPetInfo((UINT)_petType); }
    const PetInfo& GetCurPet() { return m_CurPet; }

public:
    CLONE_DISABLE(CPet);

public:
    CPet();
    ~CPet();
};

