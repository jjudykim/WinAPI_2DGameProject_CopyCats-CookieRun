#pragma once
#include "CLevel.h"

class CSound;
class CPanelUI;
class CImageUI;
class CButtonUI;

class CLevel_Lobby
	: public CLevel
{
private:
	Vec2D				m_Resolution;
	CSound*				m_BGM;
	CImageUI*			m_CurCookieUI;
	CImageUI*			m_CurPetUI;

	CPanelUI*			m_SelectCookiePanel;
	CPanelUI*			m_EmptyCookiePanel;

	CPanelUI*			m_SelectPetPanel;
	CButtonUI*			m_SelectPetBtn;

	vector<int>			m_vecScore;

	vector<wstring>		m_vecCookieStr;
	vector<CPanelUI*>	m_vecCookiePanel;
	vector<CButtonUI*>  m_vecCookieBtn;
	wstring				m_SelectCookieStr;

	vector<wstring>		m_vecPetStr;
	vector<CPanelUI*>	m_vecPetPanel;
	vector<CButtonUI*>  m_vecPetBtn;
	wstring				m_SelectPetStr;

	CButtonUI*			m_PageChangeBtn;
	CPanelUI*			m_LoadingPanel;

	bool				m_SelectingCookie;
	int					m_CurPanelStartIndex;

public:
	virtual void begin() override;
	virtual void tick() override;

	virtual void Enter() override;
	virtual void Exit() override;

public:
	void LoadSoundResource();
	void LoadTextureResource();
	void SetEpisodeMapUI();
	void SetSelectCookieUI();
	void SetSelectPetUI();

	void UpdateSelectCookieUI();
	void UpdateSelectPetUI();

	void SpawnSelectCookieUI();
	void SpawnSelectPetUI();

	void DeleteSelectCookieUI();
	void DeleteSelectPetUI();

	void FindSelectCookieByBtn(CButtonUI* _btn);
	void FindSelectPetByBtn(CButtonUI* _btn);

	void LoadCookieList();
	void LoadPetList();

	void ShowLoadingUI();
public:
	void SetCurPanelStartIndex(int _index) { m_CurPanelStartIndex = _index; }
	int GetCurPanelStartIndex() { return m_CurPanelStartIndex; }
	int GetCountOfCookies() { return m_vecCookieStr.size(); }
	int GetCountOfPets() { return m_vecPetStr.size(); }
public:

public:
	CLONE_DISABLE(CLevel_Lobby);

public:
	CLevel_Lobby();
	~CLevel_Lobby();
};

