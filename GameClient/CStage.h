#pragma once
#include "CEntity.h"
#include "CTile.h"

class CBackground;
class CPlatform;
class CObstacle;
class CTile;


class CStage :
    public CEntity
{
private:
	EPISODE_TYPE			  m_EpisodeType;
	STAGE_TYPE				  m_StageType;
	float					  m_StageLength;

	CTile*				      m_DNObjTile;
	CBackground*			  m_arrBG[(UINT)BG_TYPE::END];
	CPlatform*				  m_arrPLT[(UINT)PLT_TYPE::END];
	CObstacle*				  m_arrOBS[(UINT)OBS_TYPE::END];
	
    vector<StageSTObjInfo>      m_vecSTObjInfo[3];                  // 0 : BG, 1 : PLT, 2 : OBS
	vector<StageDNObjInfo>      m_vecDNObjInfo;                    

public:
	void Enter();
	void Exit();

public:
	void SetTile(CTile* _Tile) { m_DNObjTile = _Tile; }
	void SetEPType(EPISODE_TYPE _Type) { m_EpisodeType = _Type; }
	void SetSTGType(STAGE_TYPE _Type) { m_StageType = _Type; }

	void AddSTObjInfo(StageSTObjInfo _info, int _index) { m_vecSTObjInfo[_index].push_back(_info); }
	void AddDNObjInfo(StageDNObjInfo _info) { m_vecDNObjInfo.push_back(_info); }
	const vector<StageSTObjInfo>& GetSTObjInfo(int _index) { return m_vecSTObjInfo[_index]; }
	const vector<StageDNObjInfo>& GetDNObjInfo() { return m_vecDNObjInfo; }
	void ClearSTObjInfo(int _index) { m_vecSTObjInfo[_index].clear(); }
	void ClearDNObjInfo() { m_vecDNObjInfo.clear(); }
	void ReleaseTile() { m_DNObjTile->ReleaseJellyData(); }

	EPISODE_TYPE GetEPType() { return m_EpisodeType; }
	STAGE_TYPE GetSTGType() { return m_StageType; }
	float GetSTGLength() { return m_StageLength; }

	CTile* GetTile() { return m_DNObjTile; }
	CBackground* GetBG(BG_TYPE _type) { return m_arrBG[(UINT)_type]; }
	CPlatform* GetPLT(PLT_TYPE _type) { return m_arrPLT[(UINT)_type]; }
	CObstacle* GetOBS(OBS_TYPE _type) { return m_arrOBS[(UINT)_type]; }

	int LoadSTObjectsFromFile();
	int LoadDNObjectsFromFile();

public:
	CLONE(CStage);
	CStage();
	// CStage(const CStage& _Other);
	~CStage();

	friend class CLevel_Game;
	friend class CStageMgr;
};

