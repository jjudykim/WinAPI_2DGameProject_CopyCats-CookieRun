#pragma once
#include "CLevel.h"

class CTexture;
class CDraw;

class CLevel_Editor :
    public CLevel
{
private:
    HMENU       m_hMenu;
    CTexture*   m_EditTex;

    CDraw*      m_CurDraw;
    bool        m_Drawable;
    bool        m_Drawing;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    vector<wstring> GetLoadedTextureKey();
    
    void SetEditTex(CTexture* _tex) { m_EditTex = _tex; }
    void SetDrawable(bool _drawable) { m_Drawable = _drawable; }
    bool GetDrawable() { return m_Drawable; }
    void SetDrawing(bool _drawing) { m_Drawing = _drawing; }
    bool GetDrawing() { return m_Drawing; }

public:
    CLONE_DISABLE(CLevel_Editor);
    CLevel_Editor();
    ~CLevel_Editor();

    friend class CDraw;
};

