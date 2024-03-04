#pragma once
#include "CObject.h"
class CObstacle :
    public CObject
{
private:
    CTexture*   m_ObstacleImg;
    CAnimator*  m_Animator;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

public:
    virtual CObstacle* Clone() { return new CObstacle(*this); }

public:
    CObstacle();
    ~CObstacle();
};

