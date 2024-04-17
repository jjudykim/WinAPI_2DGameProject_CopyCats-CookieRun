#pragma once
#include "CLevel.h"

class CTexture;

class CLevel_Logo :
    public CLevel
{
private:
	CTexture* m_CILogo;
	CTexture* m_OpeningBG;
	CTexture* m_OpeningLogo;

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

