#include "pch.h"
#include "CLevelMgr.h"

#include "CEngine.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CLevel.h"
#include "CLevel_Editor.h"
#include "CLevel_Logo.h"
#include "CLevel_Game.h"
#include "CLevel_Lobby.h"


CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_CurrentLevelType(LEVEL_TYPE::END)
	, m_pCurrentLevel(nullptr)
{}

CLevelMgr::~CLevelMgr()
{
	Safe_Del_Arr(m_arrLevel);
}


void CLevelMgr::init()
{
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new CLevel_Editor;
	m_arrLevel[(UINT)LEVEL_TYPE::LOGO_START] = new CLevel_Logo;
	m_arrLevel[(UINT)LEVEL_TYPE::LOBBY] = new CLevel_Lobby;
	m_arrLevel[(UINT)LEVEL_TYPE::GAME] = new CLevel_Game;

	m_CurrentLevelType = LEVEL_TYPE::LOGO_START;
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
	m_CurrentLevelType = _NextLevelType;
	assert(m_pCurrentLevel);

	m_pCurrentLevel->Enter();
	m_pCurrentLevel->begin();
}

CObject* CLevelMgr::FindObjectByName(const wstring& _strName)
{
	return m_pCurrentLevel->FindObjectByName(_strName);
}