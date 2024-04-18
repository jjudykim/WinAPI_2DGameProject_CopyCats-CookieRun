#pragma once
#include "CUI.h"
class CPanelUI :
    public CUI
{

private:
    Vec2D m_vDownPos;

public:
    virtual void tick_ui() override;
    virtual void LButtonDown() override;
    virtual void LButtonClicked() override;

public:
    CLONE(CPanelUI);
    CPanelUI();
    ~CPanelUI();

};

