#pragma once

class CTexture;
class CAnimation;
class CSound;

class CResourceMgr
{
	SINGLE(CResourceMgr);

private:
	map<wstring, CTexture*>		m_mapTex;
	map<wstring, CSound*>		m_mapSound;
	map<wstring, CAnimation*>	m_mapAnim;
	map<wstring, CookieInfo>	m_mapCookieInfo;

public:
	void init();

	CTexture* CreateTexture(const wstring& _Key, UINT _Width, UINT _Height);
	CTexture* LoadTexture(const wstring& _Key, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _Key);

	void SaveAnimation(CAnimation* _TargetAnim, const wstring& _Key, const wstring& _strRelativePath);
	CAnimation* LoadAnimation(const wstring& _Key, const wstring& _strRelativePath);
	CAnimation* FindAnimation(const wstring& _Key);

	void AddCookieInfo(const wstring& _Key, CookieInfo);
	CookieInfo FindCookieInfo(const wstring& _Key);

	friend class CLevel_Editor;
};

