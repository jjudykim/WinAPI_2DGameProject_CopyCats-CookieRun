#pragma once
#include "CObject.h"
class CObstacle :
    public CObject
{
private:
    OBS_TYPE    m_type;
    CTexture* m_ObstacleImg;
    CAnimator* m_Animator;
    CCollider* m_Collider;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

public:
    void SetOBSType(OBS_TYPE _type) { m_type = _type; }

    virtual CObstacle* Clone() { return new CObstacle(*this); }

public:
    CObstacle();
    CObstacle(UINT _typeIndex);
    ~CObstacle();
};

