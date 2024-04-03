#pragma once
#include "CObject.h"

class CPlatform :
    public CObject
{
private:
    bool        m_Edge;
    PLT_TYPE    m_Type;
    CTexture*   m_Texture;
    CCollider*  m_Collider;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;
    virtual void BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;

    CLONE(CPlatform)

public:
    CTexture* GetTexture() { return m_Texture; }
    void SetPLTType(PLT_TYPE _type) { m_Type = _type; }
    void SetTexture(CTexture* _tex) { m_Texture = _tex; }
    void SetEdge(bool _b) { m_Edge = _b; }

public:
    CPlatform();
    CPlatform(const CPlatform& _Other);
    ~CPlatform();
    
};

