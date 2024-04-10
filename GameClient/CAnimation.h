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
    void SetAtlasTexture(CTexture* _Atlas) { m_Atlas = _Atlas; }
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
    void AddAnimFrm(AniFrm _frm) { m_vecFrm.push_back(_frm); }
    int GetFrameCount() { return m_vecFrm.size(); }
    CTexture* GetAtlas() { return m_Atlas; }
    Vec2D GetColliderPos() { return m_ColliderInfo[0]; }
    Vec2D GetColliderSize() { return m_ColliderInfo[1]; }

    void ConvertFPSToDuration(int FPS)
    {
        for (int i = 0; i < m_vecFrm.size(); ++i)
        {
            m_vecFrm[i].Duration = 0.5f / (float)FPS;
        }
        
    }

    AniFrm GetFrame(int _Idx) { return m_vecFrm[_Idx]; }
    void SetFrame(int _Idx, AniFrm _frm) { m_vecFrm.at(_Idx) = _frm; }
    void DeleteFrm(int _index) 
    {
        vector<AniFrm>::iterator iter = m_vecFrm.begin();
        iter += _index;
        m_vecFrm.erase(iter);
    }

public:
    void finaltick();
    void render();
    void render(int);
    void render(char);
    void render(float);

public:
    CLONE(CAnimation);

    CAnimation();
    ~CAnimation();

    friend class CAnimator;
    friend class CResourceMgr;
};

