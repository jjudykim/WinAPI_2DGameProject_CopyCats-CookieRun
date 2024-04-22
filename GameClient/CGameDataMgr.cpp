#include "pch.h"
#include "CGameDataMgr.h"

#include "CCamera.h"
#include "CPathMgr.h"
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
	ResetForGame();
}

void CGameDataMgr::LoadFromFile()
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"GameData.data";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"r");

	if (nullptr == pFile) { return; }

	wchar_t szReadBuff[256] = {};

	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		wstring strRead = szReadBuff;

		if (strRead == L"[HIGHSCORE]")
		{
			fwscanf_s(pFile, L"%d", &m_HighGameScore);
		}
		fwscanf_s(pFile, L"%s", szReadBuff, 256);
		fwscanf_s(pFile, L"%d", &m_GlobalGameCoin);

		fwscanf_s(pFile, L"%s", szReadBuff, 256);
		fwscanf_s(pFile, L"%s", szReadBuff, 256);
		m_CurPlayCookie = wstring(szReadBuff);

		fwscanf_s(pFile, L"%s", szReadBuff, 256);
		fwscanf_s(pFile, L"%s", szReadBuff, 256);
		m_CurPlayPet = wstring(szReadBuff);
	}
	fclose(pFile);
}

void CGameDataMgr::SaveToFile()
{
	if (m_CurGameCoin != 0)
	{
		m_GlobalGameCoin += m_CurGameCoin;
	}
	if (m_HighGameScore <= m_CurGameScore)
	{
		m_HighGameScore = m_CurGameScore;
	}

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"GameData.data";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"w");

	if (pFile == nullptr)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"게임 기록 저장 실패");
		return;
	}

	fwprintf_s(pFile, L"[HIGHSCORE] ");
	fwprintf_s(pFile, L"%d\n", m_HighGameScore);

	fwprintf_s(pFile, L"[COIN] ");
	fwprintf_s(pFile, L"%d\n", m_GlobalGameCoin);

	fwprintf_s(pFile, L"[PLAYCOOKIE] ");
	fwprintf_s(pFile, L"%s\n", m_CurPlayCookie.c_str());

	fwprintf_s(pFile, L"[PLAYPET] ");
	fwprintf_s(pFile, L"%s\n", m_CurPlayPet.c_str());
	
	fclose(pFile);
}

void CGameDataMgr::tick()
{
	/*if (m_HighGameScore < m_CurGameScore)
	{
		m_HighGameScore = m_CurGameScore;
	}*/
}

void CGameDataMgr::ResetForGame()
{
	LoadFromFile();
	m_MaxHP = 100;
	m_CurHP = m_MaxHP;
	m_CurGameScore = 0;
	m_CookieDead = false;
}
