#pragma once
#include "CObject.h"
class CPlayer :
    public CObject
{
private:

public:
    virtual void begin();
    virtual void tick();
    virtual void render();

public:
    virtual CObject* Clone() override { return new CPlayer(*this); }

public:
    CPlayer();
    ~CPlayer();
};

