#pragma once
#include "CObject.h"

class CCollider;

class CJelly :
    public CObject
{
private:
    JELLY_TYPE  m_type;

    CCollider* m_Collider;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

public:
    JELLY_TYPE GetJellyType() { return m_type; }
    void SetJellyType(JELLY_TYPE _type) { m_type = _type; }

public:
    CLONE(CJelly);

public:
    CJelly();
    CJelly(JELLY_TYPE _type);
    ~CJelly();
    
};

