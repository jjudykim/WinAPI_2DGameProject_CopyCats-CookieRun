#pragma once
#include "CObject.h"

class CCollider;

class CJelly :
    public CObject
{
private:
    DYNAMIC_OBJ_TYPE    m_ObjType;
    UINT                m_Index;
    int                 m_Value;
    AtlasInfo           m_AtlasInfo;
    CTexture*           m_Texture;
    CSound*             m_Sound;

    CAnimator*          m_Animator;
    CCollider*          m_Collider;

    bool                m_UseMouse;
    bool                m_MouseOn;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

    virtual void BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;
    virtual void EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider) override;

public:
    void SetObjType(DYNAMIC_OBJ_TYPE _Type) { m_ObjType = _Type; }
    void SetIndex(UINT _Index) { m_Index = _Index; }
    void SetSound(CSound* _sound) { m_Sound = _sound; }
    void SetValue(int _Value) { m_Value = _Value; }
    void SetAtlasInfo(AtlasInfo _Info) { m_AtlasInfo = _Info; }
    void SetTexture(CTexture* _Tex) { m_Texture = _Tex; }
    void SetUseMouseOn(bool _use) { m_UseMouse = _use; }
    bool IsMouseOn() { return m_MouseOn; }

    DYNAMIC_OBJ_TYPE GetObjType() { return m_ObjType; }
    CSound* GetSound() { return m_Sound; }
    Vec2D GetAtlasStartPos() { return m_AtlasInfo.StartPos; }
    Vec2D GetAtlasSliceSize() { return m_AtlasInfo.SliceSize; }
    CTexture* GetTexture() { return m_Texture; }
    UINT GetIndex() { return m_Index; }

public:
    void CheckMouseOn();

public:
    CLONE(CJelly);

public:
    CJelly();
    CJelly(const CJelly& _Other);
    ~CJelly();
    
};

