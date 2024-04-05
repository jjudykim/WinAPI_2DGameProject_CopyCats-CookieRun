#pragma once
#include "CPlayerState.h"

class CJumpState
	: public CPlayerState
{
private:
	bool    m_Jumping;
	bool	m_JumpHigherStandard;
	float	m_JumpStandard;

private:
	virtual void Set() override;
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


	CLONE_DISABLE(CJumpState)
public:
	CJumpState();
	~CJumpState();
};

