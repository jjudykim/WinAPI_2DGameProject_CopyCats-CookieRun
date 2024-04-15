#pragma once
#include "CObject.h"

class CTile :
    public CObject
{
private:
    UINT        m_Row;
    UINT        m_Col;

    UINT        m_EditRow;
    UINT        m_EditCol;

    Vec2D       m_TileSize;
    char**      m_JellyData;



public:
    void SetRow(UINT _Row) { m_Row = _Row; }
    void SetCol(UINT _Col) { m_Col = _Col; }
    void SetRowCol(UINT _Row, UINT _Col)
    {
        m_Row = _Row;
        m_Col = _Col;
    }
    void SetEditRowCol(UINT _Row, UINT _Col)
    {
        m_EditRow = _Row;
        m_EditCol = _Col;
    };

    UINT GetRow() { return m_Row; }
    UINT GetCol() { return m_Col; }

private:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

private:
    void render_grid();

public:
    Vec2D CorrectClickedTile(Vec2D _ClickedPos);
    bool CheckJellyOnTile(Vec2D _ClickedPos);

    UINT ConvertToColFromMousePos(Vec2D _ClickedPos);
    UINT ConvertToRowFromMousePos(Vec2D _ClickedPos);

    UINT ConvertToColFromRealPos(Vec2D _RealPos);
    UINT ConvertToRowFromRealPos(Vec2D _RealPos);

    char* GetJellyDataByCol(UINT _Col) { return m_JellyData[_Col]; }
    void InitJellyData();
    void ReleaseJellyData();
    void SetJellyData(char _Data) { m_JellyData[m_EditCol][m_EditRow] = _Data; }
    bool IsFilledJellyData(UINT _Col, UINT _Row) { return m_JellyData[_Col][_Row] != (char)-1; }

    void SaveToFile(const wstring& _FullPath);
    void LoadFromFile(const wstring& _FullPath);
    CLONE(CTile);

public:
    CTile();
    //CTile(const CTile& _Other);
    ~CTile();
};

