#pragma once
#include "CAsset.h"

class CTexture :
    public CAsset
{
private:
    HDC         m_hDC;
    HBITMAP     m_hBit;
    BITMAP      m_Info;

private:
    int Create(UINT _Width, UINT _Height);
    virtual int Load(const wstring& _strFilePath) override;

public:
    HDC GetDC() { return m_hDC; }
    HBITMAP GetBit() { return m_hBit; }
    UINT GetWidth() { return m_Info.bmWidth; }
    UINT GetHeight() { return m_Info.bmHeight; }

public:
    CTexture();
    ~CTexture();

    

    friend class CAssetMgr;
};

