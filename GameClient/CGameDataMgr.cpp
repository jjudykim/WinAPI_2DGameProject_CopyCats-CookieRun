#include "pch.h"
#include "CGameDataMgr.h"

#include "CCamera.h"
#include "CDbgRenderMgr.h"

CGameDataMgr::CGameDataMgr()
	: m_MaxHP(0)
	, m_CurHP(0)
	, m_CurGameScore(0)
	, m_HighGameScore(0)
	, m_GlobalGameCoin(0)
	, m_CurGameCoin(0)
	, m_CookieDead(false)
	, m_BonusTime{0}
{

}

CGameDataMgr::~CGameDataMgr()
{
}

void CGameDataMgr::init()
{
	m_MaxHP = 100;
	m_CurHP = m_MaxHP;
	m_HighGameScore = 72837;
	m_GlobalGameCoin = 1723;
	m_CurGameScore = 0;
	m_CookieDead = false;
}

void CGameDataMgr::tick()
{
	/*if (m_HighGameScore < m_CurGameScore)
	{
		m_HighGameScore = m_CurGameScore;
	}*/
}
