#pragma once
#include "CComponent.h"

class CTexture;
class CAnimation;

class CAnimator :
    public CComponent
{

private:
    map<wstring, CAnimation*> m_mapAnim;
    CAnimation*               m_CurAnim;

public:
    virtual void finaltick() override;
    void render();

public:
    void CreateAnimation(const wstring& _AnimName, CTexture* _Atlas, Vec2D _StartPos, Vec2D _SliceSize, int _FrameCount, int _FPS);
    CAnimation* FindAnimation(const wstring& _AnimName);
    void LoadAnimation(const wstring& _strRelativeFilePath);
    void Play(wstring& _AnimName, bool _Repeat);

public:
    CLONE(CAnimator);
    CAnimator();
    ~CAnimator();

};

