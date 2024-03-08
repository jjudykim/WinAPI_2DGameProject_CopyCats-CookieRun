#include "pch.h"
#include "CLevelMgr.h"

#include "CEngine.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CLevel.h"
#include "CLevel_Stage01.h"


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

	m_CurrentLevelType = LEVEL_TYPE::STAGE_01;
	::ChangeLevel(m_CurrentLevelType);
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
	if (m_pCurrentLevel == nullptr)
		return;

	m_pCurrentLevel->render();
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _NextLevelType)
{
	if (m_arrLevel[(UINT)_NextLevelType] == m_pCurrentLevel)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"현재 레벨과 변경하려는 레벨이 동일합니다.");
		return;
	}

	if (m_pCurrentLevel)
	{
		m_pCurrentLevel->Exit();
	}

	m_pCurrentLevel = m_arrLevel[(UINT)_NextLevelType];
	assert(m_pCurrentLevel);

	m_pCurrentLevel->Enter();
	m_pCurrentLevel->begin();
}

CObject* CLevelMgr::FindObjectByName(const wstring& _strName)
{
	return m_pCurrentLevel->FindObjectByName(_strName);
}