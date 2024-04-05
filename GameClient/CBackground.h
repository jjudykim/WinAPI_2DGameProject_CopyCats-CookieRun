#pragma once
#include "CObject.h"

class CTexture;

class CBackground :
    public CObject
{
private:
    BG_TYPE            m_type;
    AtlasInfo          m_AtlasInfo; 
    CTexture*          m_BGAtlas;

public:
    virtual void tick() override;
    virtual void render() override;

public:
    BG_TYPE GetBGType() { return m_type; }
    void SetBGType(BG_TYPE _type) { m_type = _type; }
    void SetAtlas(CTexture* _tex) { m_BGAtlas = _tex; }
    void SetAtlasInfo(Vec2D _StartPos, Vec2D _SlicePos);

    CLONE(CBackground);
public:
    CBackground();
    CBackground(const CBackground& _Other);
    ~CBackground();

    
    
};

