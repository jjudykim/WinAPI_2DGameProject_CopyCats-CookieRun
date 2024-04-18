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

    bool                      m_Repeat;

public:
    virtual void finaltick() override;
    void render();                           // x, y가 기준
    void render(float);                      // Player Animation 전용 render
    void render(char);                       // x, y * 2가 기준
    void render(bool);                       // Image UI 전용 render

public:
    CAnimation* FindAnimation(const wstring& _AnimName);
    void LoadAnimation(const wstring& _Key, const wstring& _strRelativeFilePath);
    void Play(const wstring& _AnimName, bool _Repeat);
    void ChangePlayingAnim(const wstring& _AnimName, bool _Repeat);
    void PlayCurAnim(bool _Repeat);

    CAnimation* GetCurAnim() { return m_CurAnim; }
public:
    CLONE(CAnimator);
    CAnimator();
    CAnimator(const CAnimator& _Other);
    ~CAnimator();

};

