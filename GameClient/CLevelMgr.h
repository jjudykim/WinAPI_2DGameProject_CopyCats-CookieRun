#pragma once

class CLevel;

class CLevelMgr
{
	SINGLE(CLevelMgr)
private:
	CLevel*		m_arrLevel[(UINT)LEVEL_TYPE::END];
	CLevel*		m_pCurrentLevel;
	LEVEL_TYPE  m_CurrentLevelType;

public:
	CObject* FindObjectByName(const wstring& _strName);

public:
	void init();
	void progress();
	void render();

	void ChangeLevel(LEVEL_TYPE _NextLevelType);

public:
	CLevel* GetCurrentLevel() { return m_pCurrentLevel; }
	LEVEL_TYPE GetCurrentLevelType() { return m_CurrentLevelType; }
};

