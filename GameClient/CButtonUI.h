#pragma once
#include "CUI.h"

class CButtonUI;

typedef void(*BUTTON_CALLBACK)(void);
typedef void(*BUTTON_CALLBACK_PARAM)(CButtonUI* _btn);

class CButtonUI :
    public CUI
{
private:
    BUTTON_CALLBACK         m_Func;
    BUTTON_CALLBACK_PARAM   m_FuncWithBtn;
    CButtonUI*              m_FuncCallBtn;

    CTexture*            m_NormalImg;
    CTexture*            m_HoverImg;

    bool                 m_State;        // 0 : Normal,  1 : Hover

public:
    void SetCallBack(BUTTON_CALLBACK _Func) { m_Func = _Func; }
    void SetCallBackParam(BUTTON_CALLBACK_PARAM _Func, CButtonUI* _btn)
    {
        m_FuncWithBtn = _Func;
        m_FuncCallBtn = _btn;
    } 

    void SetNormalImage(CTexture* _Tex) { m_NormalImg = _Tex; }
    void SetHoverImage(CTexture* _Tex) { m_HoverImg = _Tex; }

    void SetButtonState(bool _state) { m_State = _state; }
 
public:
    virtual void tick_ui() override;
    virtual void render_ui() override;
    virtual void LButtonClicked() override;

public:
    CLONE(CButtonUI);
    CButtonUI();
    ~CButtonUI();
};

