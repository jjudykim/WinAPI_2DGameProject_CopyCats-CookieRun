#pragma once

class CLevel;

class CLevelMgr
{
	SINGLE(CLevelMgr)
private:
	CLevel*		m_arrLevel[(UINT)LEVEL_TYPE::END];
	CLevel*		m_pCurrentLevel;

public:
	void init();
	void progress();
	void render();

public:
	CLevel* GetCurrentLevel() { return m_pCurrentLevel; }
};

