#pragma once
#include "CPlayerState.h"
class CDeadByObsState :
    public CPlayerState
{
private:
	virtual void Set() override;
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


	CLONE_DISABLE(CDeadByObsState);

public:
	CDeadByObsState();
	~CDeadByObsState();
};

