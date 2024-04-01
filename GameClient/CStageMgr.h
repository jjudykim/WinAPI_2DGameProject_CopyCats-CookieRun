#pragma once

class CStage;

class CStageMgr
{
	SINGLE(CStageMgr)
private:
	vector<CStage*>   m_arrStage[(UINT)EPISODE_TYPE::END];
	CStage*			  m_pCurrentStage;
	STAGE_TYPE		  m_CurrentStageType;

public:
	void init();
	void progress();

	void ChangeNextStage();
	void LoadStageInfo(EPISODE_TYPE _EPType);

public:
	CStage* GetCurrentStage() { return m_pCurrentStage; }
};

