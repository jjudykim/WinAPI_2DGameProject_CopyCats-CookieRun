#pragma once
#include "CLevel.h"

class CLevel_Game :
    public CLevel
{
private:
    vector<BGInfo>      m_vecBGInfo;
    vector<OBSInfo>     m_vecOBSInfo;
    vector<PLTInfo>     m_vecPLTInfo;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    CLONE_DISABLE(CLevel_Game);

public:
    CLevel_Game();
    ~CLevel_Game();
};

