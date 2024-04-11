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

	void SetStartStage(EPISODE_TYPE _Ep) 
	{ 
		LoadStageInfo(_Ep);
		m_pCurrentStage = m_arrStage[(UINT)_Ep].at(0);
	}
	void ChangeNextStage();
	void LoadStageInfo(EPISODE_TYPE _EPType);
	void SaveStageSTObject(CStage* _SaveStage);
	void SaveStageDNObject(CStage* _SaveStage);

public:
	CStage* GetCurrentStage() { return m_pCurrentStage; }
	CStage* GetStage(UINT _Episode, UINT _Stage) { return m_arrStage[_Episode].at(_Stage); }
};

