#include "pch.h"
#include "CLevel_Game.h"

#include "CCollisionMgr.h"

#include "CPlayer.h"
#include "CBackground.h"
#include "CPlatform.h"
#include "CObstacle.h"
#include "CPathMgr.h"
#include "CStage.h"

CLevel_Game::CLevel_Game()
{
	
}

CLevel_Game::~CLevel_Game()
{
}

void CLevel_Game::begin()
{
	CLevel::begin();
}

void CLevel_Game::tick()
{
	CLevel::tick();
}

void CLevel_Game::Enter()
{
	// 현재 스테이지 맵 데이터 불러오기
	m_CurStage = new CStage();
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"stage\\Ep1_1st_stage.stg";
	LoadFromFile(strFilePath);

	// 다음 스테이지 맵 데이터 불러오기
	//...

	CObject* pObject = new CPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(COOKIE_DEFAULT_POSX, COOKIE_DEFAULT_POSY);
	pObject->SetScale(100.f, 200.f);
	pObject->SetSpeed(400.f);
	AddObject(LAYER_TYPE::PLAYER, pObject);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::JELLY);

	CCamera::GetInst()->SetCameraFocus();
}

void CLevel_Game::Exit()
{
}

void CLevel_Game::LoadFromFile(const wstring& _FullPath)
{
	m_CurStage->LoadFromFile(_FullPath);
	
	const vector<StageObjInfo>& vecStageInfo = m_CurStage->GetStageInfo();

	CObject* pObject = nullptr;

	for (size_t i = 0; i < vecStageInfo.size(); ++i)
	{
		LAYER_TYPE type = vecStageInfo[i]._objType;
		UINT index = vecStageInfo[i]._typeIndex;
		if (type == LAYER_TYPE::BACKGROUND)	pObject = new CBackground(index);
		else if (type == LAYER_TYPE::PLATFORM) pObject = new CPlatform(index);
		else if (type == LAYER_TYPE::OBSTACLE) pObject = new CObstacle(index);

		pObject->SetPos(vecStageInfo[i]._startPos);
		pObject->SetScale(vecStageInfo[i]._scale);
		pObject->SetSpeed(vecStageInfo[i]._speed);

		pObject->SetImage(CAssetMgr::GetInst()->LoadTexture(vecStageInfo[i]._imageName, vecStageInfo[i]._path));
		pObject->SetAtlasInfo(vecStageInfo[i]._atlas, vecStageInfo[i]._slicePos, vecStageInfo[i]._sliceSize);

		AddObject(pObject->GetLayerType(), pObject);
	}
}


