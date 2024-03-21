#pragma once
#include "CLevel.h"

class CTexture;

class CLevel_Editor :
    public CLevel
{
private:
    HMENU       m_hMenu;
    CTexture*   m_editTex;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    vector<wstring> GetLoadedTextureKey();
    
    void SetEditTex(CTexture* _tex) { m_editTex = _tex; }

public:
    CLONE_DISABLE(CLevel_Editor);
    CLevel_Editor();
    ~CLevel_Editor();
};

