#include "pch.h"
#include "CGameDataMgr.h"

#include "CCamera.h"
#include "CDbgRenderMgr.h"

CGameDataMgr::CGameDataMgr()
	: m_MaxHP(0)
	, m_CurHP(0)
	, m_CurGameScore(0)
	, m_HighGameScore(0)
	, m_CookieDead(false)
{

}

CGameDataMgr::~CGameDataMgr()
{
}

void CGameDataMgr::init()
{
	m_MaxHP = 300;
	m_CurHP = m_MaxHP;
	m_HighGameScore = 5000;
	m_CurGameScore = 0;
	m_CookieDead = false;
}

void CGameDataMgr::tick()
{
	DbgObjInfo HighScoreInfo = { CCamera::GetInst()->GetRealPos(Vec2D(1100, 100)), 0,
								L"High Score : " + std::to_wstring(m_HighGameScore) };

	DbgObjInfo CurScoreInfo = { CCamera::GetInst()->GetRealPos(Vec2D(1100, 120)), 0,
								L"Current Score : " + std::to_wstring(m_CurGameScore) };

	CDbgRenderMgr::GetInst()->AddDbgObjInfo(HighScoreInfo);
	CDbgRenderMgr::GetInst()->AddDbgObjInfo(CurScoreInfo);
}
