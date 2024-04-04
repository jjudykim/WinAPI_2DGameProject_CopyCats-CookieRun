#pragma once
#include "CObject.h"
class CObstacle :
    public CObject
{
private:
    OBS_TYPE    m_Type;
    CTexture*   m_Texture;
    CAnimator*  m_Animator;
    CCollider*  m_Collider;

    bool        m_UseMouse;
    bool        m_MouseOn;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

public:
    void SetUseMouseOn(bool _use) { m_UseMouse = _use; }
    bool IsMouseOn() { return m_MouseOn; }
    void SetOBSType(OBS_TYPE _type) { m_Type = _type; }
    void SetTexture(CTexture* _tex) { m_Texture = _tex; }

    CTexture* GetTexture() { return m_Texture; }
    OBS_TYPE GetOBSType() { return m_Type; }

    void CheckMouseOn();
    
    CLONE(CObstacle);

public:
    CObstacle();
    CObstacle(const CObstacle& _Other);
    ~CObstacle();
};

