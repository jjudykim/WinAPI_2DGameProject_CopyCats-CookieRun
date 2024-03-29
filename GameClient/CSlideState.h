#pragma once
#include "CPlayerState.h"

class CSlideState
	: public CPlayerState
{
private:

private:
	virtual void Set() override;
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


	CLONE_DISABLE(CSlideState)
public:
	CSlideState();
	~CSlideState();
};

