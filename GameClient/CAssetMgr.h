#pragma once

class CTexture;
class CSound;

class CAssetMgr
{
	SINGLE(CAssetMgr);

private:
	map<wstring, CTexture*> m_mapTex;
	map<wstring, CSound*> m_mapSound;

public:
	void init();

	CTexture* LoadTexture(const wstring& _Key, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _Key);

	friend class CLevel_Editor;
};

