#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    CCollider* m_CollidingCol;

    Vec2D      m_Scale;

    Vec2D      m_OffsetPos;
    Vec2D      m_FinalPos;

    UINT       m_OverlapCount;

public:
    void SetOffsetPos(Vec2D _Offset) { m_OffsetPos = _Offset; }
    void SetScale(Vec2D _Scale) { m_Scale = _Scale; }

    CCollider* GetCollidingCol() { return m_CollidingCol; }
    Vec2D GetFinalPos() { return m_FinalPos; }
    Vec2D GetScale() { return m_Scale; }
    int GetOverlapCount() { return m_OverlapCount; }

private:
    void BeginOverlap(CCollider* _OtherCollider);
    void OnOverlap(CCollider* _OtherCollider);
    void EndOverlap(CCollider* _OtherCollider);

public:
    virtual void finaltick() override;
    CLONE(CCollider);

public:
    CCollider();
    CCollider(const CCollider& _Other);
    ~CCollider();

    friend class CCollisionMgr;
};

