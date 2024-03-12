#include "pch.h"
#include "CLevel_Game.h"

#include "CPlayer.h"

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
	// 다음 스테이지 맵 데이터 불러오기

	CObject* pObject = new CPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(COOKIE_DEFAULT_POSX, COOKIE_DEFAULT_POSY);
	pObject->SetScale(100.f, 200.f);
	pObject->SetSpeed(400.f);
	AddObject(LAYER_TYPE::PLAYER, pObject);
	
}

void CLevel_Game::Exit()
{
}

void CLevel_Game::LoadFromFile(const wstring& _FullPath)
{
	
}


