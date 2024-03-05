#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    Vec2D m_Scale;

    Vec2D m_OffsetPos;
    Vec2D m_FinalPos;

    UINT m_OverlapCount;

public:
    void SetOffsetPos(Vec2D _Offset) { m_OffsetPos = _Offset; }
    void SetScale(Vec2D _Scale) { m_Scale = _Scale; }

    Vec2D GetFinalPos() { return m_FinalPos; }
    Vec2D GetScale() { return m_Scale; }

private:
    void BeginOverlap(CCollider* _OtherCollider);
    void OnOverlap(CCollider* _OtherCollider);
    void EndOverlap(CCollider* _OtherCollider);

public:
    virtual void finaltick() override;
    CLONE(CCollider);

public:
    CCollider();
    ~CCollider();

    friend class CCollisionMgr;
};

