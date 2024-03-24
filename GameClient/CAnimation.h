#pragma once
#include "CEntity.h"

class CAnimator;
class CTexture;

class CAnimation :
    public CEntity
{
private:
    CAnimator*      m_Animator;
    CTexture*       m_Atlas;
    vector<AniFrm>  m_vecFrm;

    Vec2D           m_ColliderInfo[2];    // [0] : Collider Pos, [1] : Collider Size
    float           m_Time;

    int             m_CurFrmIdx;
    bool            m_bFinish;

public:
    void Create(CTexture* _AtlasTex, Vec2D _StartPos, Vec2D _SliceSize, int _DividerSize, int _FrameCount, int _FPS);
    void Create(CTexture* _AtlasTex, int _FrameCount, const AniFrm& _frm);
    bool IsFinish() { return m_bFinish; }
    void SetAtlasTexture(CTexture* _Atlas) { m_Atlas = m_Atlas; }
    void SetColliderInfo(Vec2D _Pos, Vec2D _Size) 
    { 
        m_ColliderInfo[0] = _Pos;
        m_ColliderInfo[1] = _Size; 
    }
    
    void Reset()
    {
        m_Time = 0.f;
        m_CurFrmIdx = 0;
        m_bFinish = false;
    }

public:
    AniFrm& GetFrame(int _Idx) { return m_vecFrm[_Idx]; }
    int GetFrameCount() { return m_vecFrm.size(); }
    CTexture* GetAtlas() { return m_Atlas; }
    Vec2D GetColliderPos() { return m_ColliderInfo[0]; }
    Vec2D GetColliderSize() { return m_ColliderInfo[1]; }

public:
    void finaltick();
    void render();
    void render(CTexture* _AtlasTex, const AniFrm& _Frm);

public:
    CLONE(CAnimation);

    CAnimation();
    ~CAnimation();

    friend class CAnimator;
    friend class CResourceMgr;
};

