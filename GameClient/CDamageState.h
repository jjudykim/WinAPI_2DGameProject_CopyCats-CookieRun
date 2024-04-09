#pragma once

#include "CPlayerState.h"

class CDamageState
	: public CPlayerState
{
private:
	float    m_Timer;

private:
	virtual void Set() override;
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


	CLONE_DISABLE(CDamageState);
public:
	CDamageState();
	~CDamageState();
};

