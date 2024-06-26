#pragma once
#include "CEntity.h"
class CAsset :
    public CEntity
{
private:
    wstring     m_Key;
    wstring     m_RelativePath;

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }

public:
    CLONE_DISABLE(CAsset);
    virtual int Load(const wstring& _strFilePath) = 0;

public:
    CAsset();
    ~CAsset();

    friend class CResourceMgr;
};

