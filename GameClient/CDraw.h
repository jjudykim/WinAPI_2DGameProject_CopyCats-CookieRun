#pragma once
#include "CObject.h"
class CDraw :
    public CObject
{
private:
    CTexture*   m_Tex;
    bool        m_Drawing;

public:
    virtual void tick() override;
    virtual void render() override;
    
public:
    bool IsDrawing() { return m_Drawing; }
    void setDrawing(bool _Drawing) { m_Drawing = _Drawing; }
    void SetTexture(CTexture* _tex) { m_Tex = _tex; }
    CTexture* GetTexture() { return m_Tex; }

public:
    CLONE_DISABLE(CDraw);
    CDraw();
    ~CDraw();
};

