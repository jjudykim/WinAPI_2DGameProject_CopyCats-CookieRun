#pragma once
#include "CLevel.h"

class CLevel_Editor :
    public CLevel
{
private:
    HMENU  m_hMenu;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    
    virtual void Exit() override;

public:
    vector<wstring> GetLoadedTextureKey();

public:
    CLONE_DISABLE(CLevel_Editor);
    CLevel_Editor();
    ~CLevel_Editor();
};

