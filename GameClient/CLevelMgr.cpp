#include "pch.h"
#include "CLevelMgr.h"

#include "CPathMgr.h"
#include "CLevel.h"
#include "CLevel_Stage01.h"

#include "CPlayer.h"
#include "CJelly.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{}

CLevelMgr::~CLevelMgr()
{
	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		if (nullptr != m_arrLevel[i])
		{
			delete m_arrLevel[i];
		}
	}
}


void CLevelMgr::init()
{
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CLevel_Stage01;

	m_pCurrentLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01];

	CObject* pObject = new CPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(200.f, 500.f);
	pObject->SetScale(100.f, 200.f);
	m_pCurrentLevel->AddObject(pObject);

	pObject = new CJelly(JELLY_TYPE::BLUE_BEAN);
	pObject->SetPos(500.f, 480.f);
	pObject->SetScale(40.f, 50.f);
	m_pCurrentLevel->AddObject(pObject);

	pObject = new CJelly(JELLY_TYPE::PINK_BEAN);
	pObject->SetPos(600.f, 480.f);
	pObject->SetScale(40.f, 50.f);
	m_pCurrentLevel->AddObject(pObject);

	pObject = new CJelly(JELLY_TYPE::GENERAL_YELLOW_BEAR);
	pObject->SetPos(700.f, 480.f);
	pObject->SetScale(60.f, 60.f);
	m_pCurrentLevel->AddObject(pObject);


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