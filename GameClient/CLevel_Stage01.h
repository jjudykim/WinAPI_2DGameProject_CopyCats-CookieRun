#pragma once
#include "CLevel.h"

class CLevel_Stage01
	: public CLevel
{
public:
	virtual void begin() override;
	virtual void tick() override;

	virtual void Enter() override;
	virtual void Exit() override;

public:
	CLONE_DISABLE(CLevel_Stage01);

public:
	CLevel_Stage01();
	~CLevel_Stage01();
};

