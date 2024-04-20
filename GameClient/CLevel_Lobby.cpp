#include "pch.h"
#include "CLevel_Lobby.h"

#include "CGameDataMgr.h"
#include "CLevelMgr.h"
#include "CKeyMgr.h"

#include "CObject.h"
#include "CSound.h"
#include "CImageUI.h"
#include "CPanelUI.h"
#include "CScoreUI.h"
#include "CButtonUI.h"

void RunBtnCallBackFunc()
{
	CSound* sound = CResourceMgr::GetInst()->FindSound(L"Effect_UIBtn");
	sound->SetVolume(80.f);
	sound->Play();
	CLevelMgr::GetInst()->ChangeLevel(LEVEL_TYPE::GAME);
}

CLevel_Lobby::CLevel_Lobby()
{
}

CLevel_Lobby::~CLevel_Lobby()
{
}


void CLevel_Lobby::begin()
{
}

void CLevel_Lobby::tick()
{
	CLevel::tick();
}


void CLevel_Lobby::Enter()
{
	m_Resolution = CEngine::GetInst()->GetResolution();

	LoadSoundResource();
	LoadTextureResource();

	CSound* sound = CResourceMgr::GetInst()->FindSound(L"Bgm_MainLobby");
	sound->SetVolume(20.f);
	sound->PlayToBGM(true);


	// UI Setting
	CImageUI* ImageUI = nullptr;
	CPanelUI* PanelUI = nullptr;
	CButtonUI* ButtonUI = nullptr;
	CScoreUI* ScoreUI = nullptr;


	// Background
	ImageUI = new CImageUI;
	ImageUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"LobbyBG", L"texture\\Lobby\\LobbyBG.png"));
	ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
	ImageUI->SetPos(m_Resolution.x / 2.f, m_Resolution.y / 2.f);
	AddObject(LAYER_TYPE::DEFAULT, ImageUI);


	// Current Cookie & Pet Panel Setting
	PanelUI = new CPanelUI;
	PanelUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"PanelBG_2", L"texture\\Lobby\\PanelBG_2.png"));
	PanelUI->SetScale(PanelUI->GetTexture()->GetWidth(), PanelUI->GetTexture()->GetHeight());
	PanelUI->SetPos(m_Resolution.x - 30.f - (PanelUI->GetScale().x / 2.f), 290.f);
	AddObject(LAYER_TYPE::UI, PanelUI);

	ImageUI = new CImageUI;
	ImageUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"CookieNPet_Select", L"texture\\Lobby\\CookieNPet_Select.png"));
	ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
	ImageUI->SetPos(m_Resolution.x - 30.f - (PanelUI->GetScale().x / 2.f), 535.f);
	AddObject(LAYER_TYPE::UI, ImageUI);



	m_CurCookieUI = new CImageUI;
	// TODO : 나중에 파일로 기본 설정값 바꾸기
	m_CurCookieUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"Brave_Cookie_Illust", L"texture\\Illustration\\Illust_Brave_Cookie.png"));
	m_CurCookieUI->SetScale(210.f, 240.f);
	m_CurCookieUI->SetPos(100.f, 0.f);
	PanelUI->AddChildUI(m_CurCookieUI);

	m_CurPetUI = new CImageUI;
	m_CurPetUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"Pet_GoldDrop_Illust", L"texture\\Illustration\\Illust_Pet_GoldDrop.png"));
	m_CurPetUI->SetScale(130.f, 130.f);
	m_CurPetUI->SetPos(-100.f, -30.f);
	PanelUI->AddChildUI(m_CurPetUI);



	// HighScore, CoinScore

	// 1) HighScore UI
	CPanelUI* HighScorePanel = nullptr;
	HighScorePanel = new CPanelUI;
	HighScorePanel->SetScale(500.f, 200.f);
	HighScorePanel->SetPos(-250.f, -115.f);

	ImageUI = new CImageUI;
	ImageUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"HighScore_Banner_Mini", L"texture\\Lobby\\HighScore_Banner_Mini.png"));
	ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
	ImageUI->SetPos(250, 30);
	HighScorePanel->AddChildUI(ImageUI);

	m_vecScore.clear();

	// Score UI Setting

	int score = CGameDataMgr::GetInst()->GetHighScore();
	while (true)
	{
		m_vecScore.push_back(score % 10);
		if (score / 10 < 1) break;
		else score /= 10;
	}
	int digit = m_vecScore.size();

	for (int i = 0; i < digit; ++i)
	{
		ScoreUI = new CScoreUI;
		ScoreUI->SetSmallScore(m_vecScore[digit - 1 - i]);
		float StartPosX = (11 - digit) * (ScoreUI->GetTexture()->GetWidth());
		ScoreUI->SetPos(StartPosX + (ScoreUI->GetTexture()->GetWidth() * i), 80.f);
		ScoreUI->SetScale(ScoreUI->GetTexture()->GetWidth(), ScoreUI->GetTexture()->GetHeight());
		HighScorePanel->AddChildUI(ScoreUI);
	}


	// 2) CoinScore UI
	CPanelUI* CoinScorePanel = nullptr;
	CoinScorePanel = new CPanelUI;
	CoinScorePanel->SetScale(500.f, 200.f);
	CoinScorePanel->SetPos(-250.f, 35.f);

	ImageUI = new CImageUI;
	ImageUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"Coin_Banner_Mini", L"texture\\Lobby\\Coin_Banner_Mini.png"));
	ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
	ImageUI->SetPos(250, 30);
	CoinScorePanel->AddChildUI(ImageUI);

	m_vecScore.clear();

	int coin = CGameDataMgr::GetInst()->GetGlobalGameCoin();
	while (true)
	{
		m_vecScore.push_back(coin % 10);
		if (coin / 10 < 1) break;
		else coin /= 10;
	}
	int coin_digit = m_vecScore.size();

	for (int i = 0; i < coin_digit; ++i)
	{
		ScoreUI = new CScoreUI;
		ScoreUI->SetSmallScore(m_vecScore[coin_digit - 1 - i]);
		float StartPosX = (8 - coin_digit) * (ScoreUI->GetTexture()->GetWidth());
		ScoreUI->SetPos(StartPosX + (ScoreUI->GetTexture()->GetWidth() * i), 80.f);
		ScoreUI->SetScale(ScoreUI->GetTexture()->GetWidth(), ScoreUI->GetTexture()->GetHeight());
		CoinScorePanel->AddChildUI(ScoreUI);
	}


	PanelUI = new CPanelUI;
	PanelUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"PanelBG_1", L"texture\\Lobby\\PanelBG_1.png"));
	PanelUI->SetScale(PanelUI->GetTexture()->GetWidth(), PanelUI->GetTexture()->GetHeight());
	PanelUI->SetPos(30.f + (PanelUI->GetScale().x / 2.f), 320.f);

	AddObject(LAYER_TYPE::UI, PanelUI);

	ImageUI = new CImageUI;
	ImageUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"Title_Record", L"texture\\Lobby\\Title_Record.png"));
	ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
	ImageUI->SetPos(0, PanelUI->GetScale().y / 2.f * (-1));
	PanelUI->AddChildUI(ImageUI);

	ImageUI = new CImageUI;
	ImageUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"RecordPanelBG", L"texture\\Lobby\\RecordPanelBG.png"));
	ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
	
	PanelUI->AddChildUI(ImageUI);
	PanelUI->AddChildUI(HighScorePanel);
	PanelUI->AddChildUI(CoinScorePanel);


	// EpisodeMap UI;

	PanelUI = new CPanelUI;
	PanelUI->SetScale(675.f, 200.f);
	PanelUI->SetPos(50.f + (PanelUI->GetScale().x / 2.f), 620.f);

	ImageUI = new CImageUI;
	ImageUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"NowEP_1", L"texture\\Lobby\\NowEP_1.png"));
	ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
	ImageUI->SetPos(100, -50);
	PanelUI->AddChildUI(ImageUI);

	ButtonUI = new CButtonUI;
	ButtonUI->SetNormalImage(CResourceMgr::GetInst()->FindTexture(L"EpisodeMap_Normal"));
	ButtonUI->SetScale(675.f, 140.f);
	ButtonUI->SetPos(0.f, 20.f);
	PanelUI->AddChildUI(ButtonUI);

	AddObject(LAYER_TYPE::UI, PanelUI);

	

	// Run Button
	ButtonUI = new CButtonUI;
	ButtonUI->SetNormalImage(CResourceMgr::GetInst()->FindTexture(L"RunButton_Normal"));
	ButtonUI->SetHoverImage(CResourceMgr::GetInst()->FindTexture(L"RunButton_Hover"));
	ButtonUI->SetCallBack(&RunBtnCallBackFunc);
	ButtonUI->SetScale(242.f, 86.f);
	ButtonUI->SetPos(m_Resolution.x - 50.f - (ButtonUI->GetScale().x / 2.f), 650.f);
	AddObject(LAYER_TYPE::UI, ButtonUI);
}

void CLevel_Lobby::Exit()
{
}

void CLevel_Lobby::LoadSoundResource()
{
	CResourceMgr::GetInst()->LoadSound(L"Bgm_MainLobby", L"sound\\Bgm_MainLobby.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_GameStart", L"sound\\Effect_GameStart.wav");
}

void CLevel_Lobby::LoadTextureResource()
{
	for (int i = 0; i < 10; ++i)
	{
		CResourceMgr::GetInst()->LoadTexture(L"SmallScore_" + std::to_wstring(i), L"texture\\HUD\\SmallScore_" + std::to_wstring(i) + L".png");
		CResourceMgr::GetInst()->LoadTexture(L"BigScore_" + std::to_wstring(i), L"texture\\HUD\\BigScore_" + std::to_wstring(i) + L".png");
	}

	CResourceMgr::GetInst()->LoadTexture(L"NowEP_1", L"texture\\Lobby\\NowEP_1.png");
	CResourceMgr::GetInst()->LoadTexture(L"NowEP_2", L"texture\\Lobby\\NowEP_2.png");
	CResourceMgr::GetInst()->LoadTexture(L"NowEP_3", L"texture\\Lobby\\NowEP_3.png");
	CResourceMgr::GetInst()->LoadTexture(L"NowEP_4", L"texture\\Lobby\\NowEP_4.png");
	CResourceMgr::GetInst()->LoadTexture(L"NowEP_5", L"texture\\Lobby\\NowEP_5.png");
	CResourceMgr::GetInst()->LoadTexture(L"EpisodeMap_Normal", L"texture\\Lobby\\EpisodeMap.png");

	// Run Button
	CResourceMgr::GetInst()->LoadTexture(L"RunButton_Normal", L"texture\\Button\\Run_Normal.png");
	CResourceMgr::GetInst()->LoadTexture(L"RunButton_Hover", L"texture\\Button\\Run_Hover.png");
}

