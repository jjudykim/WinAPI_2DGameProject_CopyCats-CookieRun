#pragma once
#include "CObject.h"

class CTile :
    public CObject
{
private:
    UINT        m_Row;
    UINT        m_Col;
    Vec2D       m_TileSize;

public:
    void SetRow(UINT _Row);
    void SetCol(UINT _Col);
    void SetRowCol(UINT _Row, UINT _Col);

    UINT GetRow() { return m_Row; }
    UINT GetCol() { return m_Col; }

private:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

private:
    void render_grid();

public:
    void SaveToFile(const wstring& _FullPath);
    void LoadFromFile(const wstring& _FullPath);
    CLONE(CTile);

public:
    CTile();
    //CTile(const CTile& _Other);
    ~CTile();
};

