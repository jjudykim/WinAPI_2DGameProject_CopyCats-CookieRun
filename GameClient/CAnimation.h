#pragma once
#include "CEntity.h"

class CAnimator;
class CTexture;

struct AniFrm
{
    Vec2D StartPos;
    Vec2D SliceSize;
    Vec2D Offset;
    float Duration;
};

class CAnimation :
    public CEntity
{
private:
    CAnimator*      m_Animator;
    CTexture*       m_Atlas;
    vector<AniFrm>  m_vecFrm;

    float           m_Time;

    int             m_CurFrmIdx;
    bool            m_bFinish;

public:
    void Create(CTexture* _AtlasTex, Vec2D _StartPos, Vec2D _SliceSize, int _FrameCount, int _FPS);
    void SetAtlasTexture(CTexture* _Atlas) { m_Atlas = m_Atlas; }
    bool IsFinish() { return m_bFinish; }
    void Reset()
    {
        m_Time = 0.f;
        m_CurFrmIdx = 0;
        m_bFinish = false;
    }

public:
    AniFrm& GetFrame(int _Idx) { return m_vecFrm[_Idx]; }

public:
    void finaltick();
    void render();

public:
    CLONE(CAnimation);

    CAnimation();
    ~CAnimation();

    friend class CAnimator;
};

