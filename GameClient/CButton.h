#pragma once
#include "CUI.h"

typedef void(*BUTTON_CALLBACK)(void);

class CButton :
    public CUI
{
private:
    BUTTON_CALLBACK      m_Func;

    CTexture*            m_NormalImg;
    CTexture*            m_HoverImg;

public:
    void SetCallBack(BUTTON_CALLBACK _Func) { m_Func = _Func; }

    void SetNormalImage(CTexture* _Tex) { m_NormalImg = _Tex; }
    void SetHoverImage(CTexture* _Tex) { m_HoverImg = _Tex; }
 
public:
    virtual void tick_ui() override;
    virtual void render_ui() override;
    virtual void LButtonClicked() override;

public:
    CLONE(CButton);
    CButton();
    ~CButton();
};

