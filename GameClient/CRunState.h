#pragma once
#include "CPlayerState.h"

class CRunState
	: public CPlayerState
{
private:

private:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


	CLONE(CRunState);
public:
	CRunState();
	~CRunState();
};

