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

	map<UINT, CookieInfo>		m_mapCookieInfo;
	map<UINT, PetInfo>			m_mapPetInfo;

public:
	void init();

	CTexture* CreateTexture(const wstring& _Key, UINT _Width, UINT _Height, bool _Alpha);
	CTexture* LoadTexture(const wstring& _Key, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _Key);

	CSound* LoadSound(const wstring& _Key, const wstring& _strRelativePath);
	CSound* FindSound(const wstring& _Key);

	void SaveAnimation(CAnimation* _TargetAnim, const wstring& _Key, const wstring& _strRelativePath);
	CAnimation* LoadAnimation(const wstring& _Key, const wstring& _strRelativePath);
	CAnimation* FindAnimation(const wstring& _Key);

	void LoadCookieInfo();
	CookieInfo FindCookieInfo(const UINT& _Key);

	void LoadPetInfo();
	PetInfo FindPetInfo(const UINT& _Key);

	friend class CLevel_Editor;
};

