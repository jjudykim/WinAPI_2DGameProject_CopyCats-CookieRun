#pragma once
#include "CLevel.h"

class CTexture;
class CImageUI;
class CButtonUI;

class CLevel_Logo :
    public CLevel
{
private:
	CImageUI*	  m_CurBG;
	CImageUI*	  m_Logo;

	CButtonUI*	  m_BtnEditMode;
	CButtonUI*	  m_BtnGameStart;

	Vec2D		  m_Resolution;
	bool		  m_OpeningDone[3];
	bool	      m_StartGame;

public:
	virtual void begin() override;
	virtual void tick() override;
	virtual void finaltick() override;
	virtual void render() override;

	virtual void Enter() override;
	virtual void Exit() override;

public:
	CLONE_DISABLE(CLevel_Logo);

public:
	CLevel_Logo();
	~CLevel_Logo();

};

