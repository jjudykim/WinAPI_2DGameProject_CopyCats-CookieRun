#pragma once
#include "CObject.h"

class CUI
	: public CObject
{
private:
	bool		m_MouseOn;

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

