#pragma once
#include "CEntity.h"
#include "CFSM.h"

class CObject;

class CState :
    public CEntity
{
private:
    CFSM*   m_Owner;

protected:
    CObject* GetObj() { return m_Owner->GetOwner(); }
    CFSM* GetFSM() { return m_Owner; }

    template<typename T>
    T& GetBlackboardData(const wstring& _DataName)
    {
        return m_Owner->GetBlackboardData<T>(_DataName);
    }

public:
    virtual void Enter() = 0;
    virtual void FinalTick() = 0;
    virtual void Exit() = 0;

public:
    CState();
    ~CState();

    friend class CFSM;
};

