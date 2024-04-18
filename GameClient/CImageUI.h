#pragma once
#include "CUI.h"

class CImageUI :
    public CUI
{
private:
    CAnimator*      m_Anim;
    bool            m_DecreaseUI;

public:
    virtual void tick_ui() override;
    virtual void render_ui() override;

    void AddAnimator(const wstring& _Key, const wstring& _Path, bool _Repeat);

public:
    void SetDecreaseUI(bool _true) { m_DecreaseUI = true; }

public:
    CLONE(CImageUI);
    CImageUI();
    ~CImageUI();
};

