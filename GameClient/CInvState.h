#pragma once
#include "CState.h"

class CInvState
	: public CState
{
public:
	virtual void Enter() override;
	virtual void FinalTick() override;
};

