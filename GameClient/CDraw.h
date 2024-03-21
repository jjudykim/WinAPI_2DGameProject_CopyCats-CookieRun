#pragma once
#include "CObject.h"
class CDraw :
    public CObject
{
private:
    bool    m_Drawing;

public:
    virtual void tick() override;
    virtual void render() override;
    
public:
    bool IsDrawing() { return m_Drawing; }
    void setDrawing(bool _Drawing) { m_Drawing = _Drawing; }
public:
    CLONE_DISABLE(CDraw);
    CDraw();
    ~CDraw();
};

