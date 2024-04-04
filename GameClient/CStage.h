#pragma once
#include "CEntity.h"

class CBackground;
class CPlatform;
class CObstacle;


class CStage :
    public CEntity
{
private:
	EPISODE_TYPE			  m_EpisodeType;
	STAGE_TYPE				  m_StageType;
	float					  m_StageLength;

	CBackground*			  m_arrBG[(UINT)BG_TYPE::END];
	CPlatform*				  m_arrPLT[(UINT)PLT_TYPE::END];
	CObstacle*				  m_arrOBS[(UINT)OBS_TYPE::END];
	
    vector<StageSTObjInfo>      m_vecStageInfo;

public:
	void Enter();
	void Exit();

public:
	void SetEPType(EPISODE_TYPE _Type) { m_EpisodeType = _Type; }
	void SetSTGType(STAGE_TYPE _Type) { m_StageType = _Type; }

	const vector<StageSTObjInfo>& GetStageInfo() { return m_vecStageInfo; }
	EPISODE_TYPE GetEPType() { return m_EpisodeType; }
	STAGE_TYPE GetSTGType() { return m_StageType; }
	CBackground* GetBG(BG_TYPE _type) { return m_arrBG[(UINT)_type]; }
	CPlatform* GetPLT(PLT_TYPE _type) { return m_arrPLT[(UINT)_type]; }
	CObstacle* GetOBS(OBS_TYPE _type) { return m_arrOBS[(UINT)_type]; }
	int LoadFromFile();

public:
	CLONE(CStage);
	CStage();
	// CStage(const CStage& _Other);
	~CStage();

	friend class CLevel_Game;
	friend class CStageMgr;
};

