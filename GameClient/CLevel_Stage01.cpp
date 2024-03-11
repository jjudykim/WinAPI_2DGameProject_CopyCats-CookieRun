#include "pch.h"
#include "CLevel_Stage01.h"

#include "CCollisionMgr.h"

#include "CObject.h"
#include "CBackground.h"
#include "CPlayer.h"
#include "CObstacle.h"
#include "CJelly.h"
#include "CPlatform.h"

CLevel_Stage01::CLevel_Stage01()
{
}

CLevel_Stage01::~CLevel_Stage01()
{
}

void CLevel_Stage01::begin()
{
	CLevel::begin();
}

void CLevel_Stage01::tick()
{
	CLevel::tick();
}

void CLevel_Stage01::Enter()
{
	CObject* pObject = new CBackground(BACKGROUND_TYPE::MAIN);
	pObject->SetName(L"Background_MAIN");
	pObject->SetPos(0.f, 0.f);
	pObject->SetScale(CEngine::GetInst()->GetResolution());
	AddObject(LAYER_TYPE::BACKGROUND, pObject);

	pObject = new CBackground(BACKGROUND_TYPE::SUB1);
	pObject->SetName(L"Background_SUB1");
	pObject->SetPos(0.f, 0.f);
	pObject->SetScale(CEngine::GetInst()->GetResolution());
	pObject->SetSpeed(10.f);
	AddObject(LAYER_TYPE::BACKGROUND, pObject);

	pObject = new CPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(200.f, GROUND_YPOS);
	pObject->SetScale(100.f, 200.f);
	pObject->SetSpeed(400.f);
	AddObject(LAYER_TYPE::PLAYER, pObject);

	pObject = new CObstacle(OBS_TYPE::JUMP);
	pObject->SetName(L"Obstacle");
	pObject->SetPos(1200.f, 550.f);
	pObject->SetScale(104.f, 135.f);
	AddObject(LAYER_TYPE::OBSTACLE, pObject);

	pObject = new CJelly(JELLY_TYPE::BLUE_BEAN);
	pObject->SetPos(1000.f, 480.f);
	pObject->SetScale(40.f, 50.f);
	AddObject(LAYER_TYPE::JELLY, pObject);

	CObject* pObjectClone = nullptr;
	for (int i = 0; i < 20; i++)
	{
		pObjectClone = pObject->Clone();
		pObjectClone->SetPos(pObject->GetPos().x + pObject->GetScale().x + 20,
			pObject->GetPos().y);
		AddObject(LAYER_TYPE::JELLY, pObjectClone);
		pObject = pObjectClone;
	}
	pObjectClone = nullptr;

	pObject = new CJelly(JELLY_TYPE::PINK_BEAN);
	pObject->SetName(L"JELLY_PINK_BEAN");
	pObject->SetPos(600.f, 480.f);
	pObject->SetScale(40.f, 50.f);
	AddObject(LAYER_TYPE::JELLY, pObject);

	pObject = new CJelly(JELLY_TYPE::GENERAL_YELLOW_BEAR);
	pObject->SetName(L"JELLY_GENERAL_YELLOW_BEAR");
	pObject->SetPos(700.f, 480.f);
	pObject->SetScale(60.f, 60.f);
	AddObject(LAYER_TYPE::JELLY, pObject);

	pObject = new CPlatform(PLATFORM_TYPE::GROUNDED);
	pObject->SetName(L"Platform");
	pObject->SetPos(60.f, 660.f);
	pObject->SetScale(124.f, 120.f);
	AddObject(LAYER_TYPE::PLATFORM, pObject);

	for (int i = 0; i < 50; i++)
	{
		pObjectClone = pObject->Clone();
		pObjectClone->SetPos(pObject->GetPos().x + pObject->GetScale().x,
			pObject->GetPos().y);
		AddObject(LAYER_TYPE::PLATFORM, pObjectClone);
		pObject = pObjectClone;
	}
	CPlatform* vLastPlatfrom = (CPlatform*)pObject;
	vLastPlatfrom->SetEdge(true);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::JELLY);

	CCamera::GetInst()->SetCameraFocus();
}

void CLevel_Stage01::Exit()
{
}

