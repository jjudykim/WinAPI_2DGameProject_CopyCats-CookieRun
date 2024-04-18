#pragma once
#include "CUI.h"
class CScoreUI :
    public CUI
{
private:
    CTexture* BigScoreNumber[10];
    CTexture* SmallScoreNumber[10];

public:
    virtual void tick_ui() override;
    virtual void render_ui() override;

public:
    void SetSmallScore(int i) { SetTexture(SmallScoreNumber[i]); }
    void SetBigScore(int i) { SetTexture(BigScoreNumber[i]); }

public:
    CLONE(CScoreUI);
    CScoreUI();
    ~CScoreUI();
};

