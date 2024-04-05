#pragma once
#include "CObject.h"

class CPlatform :
    public CObject
{
private:
    PLT_TYPE    m_Type;
    CTexture*   m_Texture;
    CCollider*  m_Collider;

    bool        m_UseMouse;
    bool        m_MouseOn;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;

    CLONE(CPlatform)

public:
    void SetUseMouseOn(bool _use) { m_UseMouse = _use; }
    bool IsMouseOn() { return m_MouseOn; }

    CTexture* GetTexture() { return m_Texture; }
    PLT_TYPE GetPLTType() { return m_Type;  }
    void SetPLTType(PLT_TYPE _type) { m_Type = _type; }
    void SetTexture(CTexture* _tex) { m_Texture = _tex; }

    void CheckMouseOn();

public:
    CPlatform();
    CPlatform(const CPlatform& _Other);
    ~CPlatform();
    
};

