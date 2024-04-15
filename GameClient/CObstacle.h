#pragma once
#include "CObject.h"

class CSound;

class CObstacle :
    public CObject
{
private:
    OBS_TYPE    m_Type;
    CTexture*   m_Texture;
    CAnimator*  m_Animator;
    CCollider*  m_Collider;

    CSound*     m_EffectSound;

    bool        m_UseMouse;
    bool        m_MouseOn;
    bool        m_Acted;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

public:
    void SetUseMouseOn(bool _use) { m_UseMouse = _use; }
    bool IsMouseOn() { return m_MouseOn; }
    void SetOBSType(OBS_TYPE _type) { m_Type = _type; }
    void SetTexture(CTexture* _tex) { m_Texture = _tex; }
    void SetEffectSound(CSound* _sound) { m_EffectSound = _sound; }
    void SetActed(bool _act) { m_Acted = _act; }
    void ObstacleDownAction();

    CTexture* GetTexture() { return m_Texture; }
    CSound* GetEffectSound() { return m_EffectSound; }
    OBS_TYPE GetOBSType() { return m_Type; }
    bool    GetActed() { return m_Acted; }

    void CheckMouseOn();
    
    CLONE(CObstacle);

public:
    CObstacle();
    CObstacle(const CObstacle& _Other);
    ~CObstacle();
};

