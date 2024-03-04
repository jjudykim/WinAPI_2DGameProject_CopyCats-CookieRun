#pragma once
#include "CObject.h"

class CPlatform :
    public CObject
{
private:
    CCollider* m_Collider;

public:
    virtual void tick();
    virtual void BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    virtual void OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;

    CLONE(CPlatform)
public:
    CPlatform();
    CPlatform(Vec2D _Scale);
    ~CPlatform();
};

