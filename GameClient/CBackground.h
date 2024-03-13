#pragma once
#include "CObject.h"

class CTexture;

class CBackground :
    public CObject
{
private:
    BG_TYPE            m_type;

public:
    virtual void tick() override;
    virtual void render() override;

public:

    CLONE(CBackground);
public:
    CBackground();
    CBackground(UINT _typeIndex);
    ~CBackground();

    
    
};

