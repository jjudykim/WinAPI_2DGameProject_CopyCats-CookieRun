#pragma once
#include "CObject.h"

class CTexture;

class CBackground :
    public CObject
{
private:
    LEVEL_TYPE      m_Level;
    BackgroundInfo  m_Info;
    CTexture*       m_BackGroundImg;
    float           m_Speed;

public:
    virtual void tick() override;
    virtual void render() override;
    
public:
    void SetBackgroundInfo(BACKGROUND_TYPE _type);

    CLONE(CBackground);
public:
    CBackground();
    CBackground(LEVEL_TYPE _Leveltype, BACKGROUND_TYPE _BGtype);
    ~CBackground();

    
    
};

