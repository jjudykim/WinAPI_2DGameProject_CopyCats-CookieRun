#include "pch.h"
#include "CLevelMgr.h"

#include "CEngine.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CLevel.h"
#include "CLevel_Stage01.h"

#include "CBackground.h"
#include "CPlayer.h"
#include "CJelly.h"
#include "CPlatform.h"


CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{}

CLevelMgr::~CLevelMgr()
{
	Safe_Del_Arr(m_arrLevel);
}


void CLevelMgr::init()
{
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CLevel_Stage01;

	LEVEL_TYPE CurLevelType = LEVEL_TYPE::STAGE_01;

	m_pCurrentLevel = m_arrLevel[(UINT)CurLevelType];

	CObject* pObject = new CBackground(CurLevelType, BACKGROUND_TYPE::MAIN);
	pObject->SetName(L"Background_MAIN");
	pObject->SetPos(0.f, 0.f);
	pObject->SetScale(CEngine::GetInst()->GetResolution());
	m_pCurrentLevel->AddObject(LAYER_TYPE::BACKGROUND, pObject);

	pObject = new CBackground(CurLevelType, BACKGROUND_TYPE::SUB1);
	pObject->SetName(L"Background_SUB1");
	pObject->SetPos(0.f, 0.f);
	pObject->SetScale(CEngine::GetInst()->GetResolution());
	pObject->SetSpeed(10.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::BACKGROUND, pObject);

	pObject = new CJelly(JELLY_TYPE::BLUE_BEAN);
	pObject->SetPos(1000.f, 480.f);
	pObject->SetScale(40.f, 50.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::JELLY, pObject);

	CObject* pObjectClone = nullptr;
	for (int i = 0; i < 20; i++)
	{
		pObjectClone = pObject->Clone();
		pObjectClone->SetPos(pObject->GetPos().x + pObject->GetScale().x + 20,
			pObject->GetPos().y);
		m_pCurrentLevel->AddObject(LAYER_TYPE::PLATFORM, pObjectClone);
		pObject = pObjectClone;
	}
	pObjectClone = nullptr;

	pObject = new CJelly(JELLY_TYPE::PINK_BEAN);
	pObject->SetName(L"JELLY_PINK_BEAN");
	pObject->SetPos(600.f, 480.f);
	pObject->SetScale(40.f, 50.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::JELLY, pObject);

	pObject = new CJelly(JELLY_TYPE::GENERAL_YELLOW_BEAR);
	pObject->SetName(L"JELLY_GENERAL_YELLOW_BEAR");
	pObject->SetPos(700.f, 480.f);
	pObject->SetScale(60.f, 60.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::JELLY, pObject);

	pObject = new CPlatform(PLATFORM_TYPE::GROUNDED);
	pObject->SetName(L"Platform");
	pObject->SetPos(60.f, 660.f);
	pObject->SetScale(124.f, 120.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLATFORM, pObject);

	for (int i = 0; i < 50; i++)
	{
		pObjectClone = pObject->Clone();
		pObjectClone->SetPos(pObject->GetPos().x + pObject->GetScale().x, 
							pObject->GetPos().y);
		m_pCurrentLevel->AddObject(LAYER_TYPE::PLATFORM, pObjectClone);
		pObject = pObjectClone;
	}

	pObject = new CPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(200.f, 300.f);
	pObject->SetScale(100.f, 200.f);
	pObject->SetSpeed(400.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLAYER, pObject);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::JELLY);

	m_pCurrentLevel->begin();

}

void CLevelMgr::progress()
{
	if (m_pCurrentLevel == nullptr)
		return;

	m_pCurrentLevel->tick();
	m_pCurrentLevel->finaltick();
}

void CLevelMgr::render()
{
	m_pCurrentLevel->render();
}