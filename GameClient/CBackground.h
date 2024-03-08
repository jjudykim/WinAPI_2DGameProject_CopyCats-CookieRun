#pragma once
#include "CObject.h"

class CTexture;

class CBackground :
    public CObject
{
private:
    BackgroundInfo  m_Info;
    CTexture*       m_BackGroundImg;

public:
    virtual void tick() override;
    virtual void render() override;
    
public:
    void SetBackgroundInfo(BACKGROUND_TYPE _type);

    CLONE(CBackground);
public:
    CBackground();
    CBackground(BACKGROUND_TYPE _BGtype);
    ~CBackground();

    
    
};

