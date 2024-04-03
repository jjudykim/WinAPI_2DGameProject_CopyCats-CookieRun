#pragma once
#include "CObject.h"
class CObstacle :
    public CObject
{
private:
    OBS_TYPE    m_type;
    CTexture*   m_Texture;
    CAnimator*  m_Animator;
    CCollider*  m_Collider;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

public:
    CTexture* GetTexture() { return m_Texture; }

    void SetOBSType(OBS_TYPE _type) { m_type = _type; }
    void SetTexture(CTexture* _tex) { m_Texture = _tex; }
    
    CLONE(CObstacle);

public:
    CObstacle();
    CObstacle(const CObstacle& _Other);
    ~CObstacle();
};

