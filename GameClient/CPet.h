#pragma once
#include "CObject.h"

#include "CFSM.h"

class CPet :
    public CObject
{
private:
    CAnimator*      m_Animator;
    CRigidBody*     m_RigidBody;
    CCollider*      m_Collider;
    CFSM*           m_FSM;

    PetInfo         m_CurPet;
    
    float           m_ChaseSpeed;

public:
    virtual void begin();
    virtual void tick();

public:
    void SetCurPet(PET_TYPE _petType) { m_CurPet = CResourceMgr::GetInst()->FindPetInfo((UINT)_petType); }
    const PetInfo& GetCurPet() { return m_CurPet; }
    bool CheckPetFSMState(const wstring& _str) { return m_FSM->GetCurState() == m_FSM->FindState(_str); }
    void ChangePetFSMState(const wstring& _str) { m_FSM->ChangeState(_str); }

public:
    CLONE_DISABLE(CPet);

public:
    CPet();
    ~CPet();
};

