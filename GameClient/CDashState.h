#pragma once
#include "CPlayerState.h"

class CDashState :
    public CPlayerState
{
private:
	virtual void Set() override;
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


	CLONE_DISABLE(CDashState);

public:
	CDashState();
	~CDashState();
};

