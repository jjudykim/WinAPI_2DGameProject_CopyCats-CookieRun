#pragma once
#include "CPetState.h"
class CPetRunState :
    public CPetState
{
private:
	virtual void Set() override;
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


	CLONE_DISABLE(CPetRunState);
public:
	CPetRunState();
	~CPetRunState();
};

