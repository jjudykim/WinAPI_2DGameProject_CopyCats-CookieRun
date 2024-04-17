#pragma once
#include "CUI.h"

class CImageUI :
    public CUI
{
public:
    virtual void tick_ui() override;

public:
    CLONE(CImageUI);
    CImageUI();
    ~CImageUI();
};

