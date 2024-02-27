#pragma once
#include "CEntity.h"

class CObject;

class CComponent :
    public CEntity
{
private:
    CObject* m_Owner;

public:
    CObject* GetOwner() { return m_Owner; }
    
public:
    virtual void finaltick() = 0;

public:
    virtual CComponent* Clone() = 0;
    

public:
    CComponent();
    ~CComponent();

    friend class CObject;
};

