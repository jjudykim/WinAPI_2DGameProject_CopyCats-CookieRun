#include "pch.h"
#include "CLevel.h"
#include "CLevelMgr.h"

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
	// TODO : 스테이지 생성 
	// m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] 

	m_pCurrentLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01];


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
