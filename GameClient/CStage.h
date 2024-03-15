#pragma once
#include "CEntity.h"

class CStage :
    public CEntity
{
private:
    vector<StageObjInfo>      m_vecStageInfo;

public:
	const vector<StageObjInfo>& GetStageInfo() { return m_vecStageInfo; }
	
	int LoadFromFile(const wstring& _FullPath);

public:
	CLONE(CStage);
	CStage();
	// CStage(const CStage& _Other);
	~CStage();

	friend class CLevel_Game;
};

