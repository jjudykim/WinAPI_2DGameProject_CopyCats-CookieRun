#pragma once
#include "CObject.h"

class CUI
	: public CObject
{
private:
	CUI*			m_ParentUI;
	vector<CUI*>	m_vecChildUI;

	Vec2D			m_vFinalPos;

	bool			m_MouseOn;

public:
	virtual void tick() override;
	virtual void render() override;

private:
	void CheckMouseOn();

public:
	CLONE(CUI);
	CUI();
	~CUI();
};

