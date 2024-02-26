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
    vector<AniFrm>  m_vecFrm;

    float           m_Time;

    int             m_CurFrmIdx;
    bool            m_bFinish;

public:
    AniFrm& GetFrame(int _Idx) { return m_vecFrm[_Idx]; }

public:
    void finaltick();
    void render();

public:
    virtual CAnimation* Clone() override { return new CAnimation(*this); }

    CAnimation();
    ~CAnimation();

    friend class CAnimator;
};

