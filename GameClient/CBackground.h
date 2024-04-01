#pragma once
#include "CObject.h"

class CTexture;

class CBackground :
    public CObject
{
private:
    BG_TYPE            m_type;
    CTexture*          m_BGAtlas;

public:
    virtual void tick() override;
    virtual void render() override;

public:
    void SetBGType(BG_TYPE _type) { m_type = _type; }
    void SetAtlas(CTexture* _tex) { m_BGAtlas = _tex; }

    CLONE(CBackground);
public:
    CBackground();
    CBackground(UINT _typeIndex);
    ~CBackground();

    
    
};

