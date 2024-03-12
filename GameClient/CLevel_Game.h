#pragma once
#include "CLevel.h"

class CStage;

class CLevel_Game :
    public CLevel
{
private:
    CStage* m_CurStage;
    CStage* m_PostStage;
    

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    void LoadFromFile(const wstring& _FullPath);
public:
    CLONE_DISABLE(CLevel_Game);

public:
    CLevel_Game();
    ~CLevel_Game();
};

