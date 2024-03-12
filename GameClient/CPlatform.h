#pragma once
#include "CObject.h"

class CPlatform :
    public CObject
{
private:
    bool        m_Edge;
    CTexture*   m_PlatformImg;
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
    void SetEdge(bool _b) { m_Edge = _b; }

public:
    CPlatform();
    CPlatform(PLT_TYPE _type);
    CPlatform(const CPlatform& _Other);
    ~CPlatform();
    
};

