#pragma once
#include "CPetState.h"

class CPetAttractState :
    public CPetState
{
private:
	virtual void Set() override;
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


	CLONE_DISABLE(CPetAttractState);
public:
	CPetAttractState();
	~CPetAttractState();
};

