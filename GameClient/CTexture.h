#pragma once
#include "CAsset.h"

class CTexture :
    public CAsset
{
private:
    HDC         m_hDC;
    Bitmap*     m_pBit;
    HBITMAP     m_hBit;
    BITMAP      m_Info;

    wstring     m_Path;

private:
    int Create(UINT _Width, UINT _Height);
    int CreateWithAlpha(UINT _Width, UINT _Height, Color _color);
    virtual int Load(const wstring& _strFilePath) override;

public:
    HDC GetDC() { return m_hDC; }
    Bitmap* GetpBit() { return m_pBit; }
    HBITMAP GetBit() { return m_hBit; }
    UINT GetWidth() { return m_Info.bmWidth; }
    UINT GetHeight() { return m_Info.bmHeight; }

    wstring GetFullPath() { return m_Path; }

public:
    CTexture();
    ~CTexture();

    

    friend class CResourceMgr;
};

