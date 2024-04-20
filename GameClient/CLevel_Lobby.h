#pragma once
#include "CLevel.h"

class CImageUI;

class CLevel_Lobby
	: public CLevel
{
private:
	Vec2D		m_Resolution;

	CImageUI*	m_CurCookieUI;
	CImageUI*	m_CurPetUI;

	vector<int> m_vecScore;


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
	

public:
	CLONE_DISABLE(CLevel_Lobby);

public:
	CLevel_Lobby();
	~CLevel_Lobby();
};

