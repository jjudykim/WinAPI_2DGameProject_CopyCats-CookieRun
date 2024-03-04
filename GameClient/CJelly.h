#pragma once
#include "CObject.h"

class CJelly :
    public CObject
{
private:
    JELLY_TYPE  m_type;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

public:
    JELLY_TYPE GetJellyType() { return m_type; }
    void SetJellyType(JELLY_TYPE _type) { m_type = _type; }

public:
    virtual CJelly* Clone() { return new CJelly(*this); }

public:
    CJelly();
    CJelly(JELLY_TYPE _type);
    ~CJelly();
    
};

