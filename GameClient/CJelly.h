#pragma once
#include "CObject.h"

class CJelly :
    public CObject
{
private:
    JELLY_TYPE  m_type;
    Vec2D       m_Data;

    CTexture*   m_JellyImg;
    CAnimator*  m_Animator;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

    CTexture* SetTextureByJellyType(JELLY_TYPE _type);

public:
    virtual CJelly* Clone() { return new CJelly(*this); }

public:
    CJelly();
    ~CJelly();
    
};

