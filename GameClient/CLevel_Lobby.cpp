#include "pch.h"
#include "CLevel_Lobby.h"

#include "CGameDataMgr.h"
#include "CPathMgr.h"
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

void EpisodeMapBtnCallBackFunc()
{

}

void SelectCookieBtnCallBackFunc()
{
	// TODO : 시작 레벨을 Logo로 변경했을 때 주석 해제
	CSound* sound = CResourceMgr::GetInst()->FindSound(L"Effect_UIBtn");
	sound->SetVolume(80.f);
	sound->Play();
	CLevel_Lobby* level = static_cast<CLevel_Lobby*>(CLevelMgr::GetInst()->GetCurrentLevel());
	level->SpawnSelectCookieUI();
}

void SelectPetBtnCallBackFunc()
{
	CSound* sound = CResourceMgr::GetInst()->FindSound(L"Effect_UIBtn");
	sound->SetVolume(80.f);
	sound->Play();
	CLevel_Lobby* level = static_cast<CLevel_Lobby*>(CLevelMgr::GetInst()->GetCurrentLevel());
	level->SpawnSelectPetUI();
}

void CloseSelectCookieBtnCallBackFunc(CButtonUI* _btn)
{
	CSound* sound = CResourceMgr::GetInst()->FindSound(L"Effect_UIBtn");
	sound->SetVolume(80.f);
	sound->Play();
	CLevel_Lobby* level = static_cast<CLevel_Lobby*>(CLevelMgr::GetInst()->GetCurrentLevel());
	level->FindSelectCookieByBtn(_btn);
	level->DeleteSelectCookieUI();
}

void CloseSelectPetBtnCallBackFunc(CButtonUI* _btn)
{
	CSound* sound = CResourceMgr::GetInst()->FindSound(L"Effect_UIBtn");
	sound->SetVolume(80.f);
	sound->Play();
	CLevel_Lobby* level = static_cast<CLevel_Lobby*>(CLevelMgr::GetInst()->GetCurrentLevel());
	level->FindSelectPetByBtn(_btn);
	level->DeleteSelectPetUI();
}

void PagePlusBtnCallBackFunc()
{
	CSound* sound = CResourceMgr::GetInst()->FindSound(L"Effect_UIBtn");
	sound->SetVolume(80.f);
	sound->Play();
	CLevel_Lobby* level = static_cast<CLevel_Lobby*>(CLevelMgr::GetInst()->GetCurrentLevel());
	if (level->GetCurPanelStartIndex() + 3 < level->GetCountOfCookies())
	{
		level->SetCurPanelStartIndex(level->GetCurPanelStartIndex() + 3);
		level->UpdateSelectCookieUI();
	}
}

void PagePlusBtnPetCallBackFunc()
{
	CSound* sound = CResourceMgr::GetInst()->FindSound(L"Effect_UIBtn");
	sound->SetVolume(80.f);
	sound->Play();
	CLevel_Lobby* level = static_cast<CLevel_Lobby*>(CLevelMgr::GetInst()->GetCurrentLevel());
	if (level->GetCurPanelStartIndex() + 3 < level->GetCountOfPets())
	{
		level->SetCurPanelStartIndex(level->GetCurPanelStartIndex() + 3);
		level->UpdateSelectPetUI();
	}
}

void PageMinusBtnCallBackFunc()
{
	CSound* sound = CResourceMgr::GetInst()->FindSound(L"Effect_UIBtn");
	sound->SetVolume(80.f);
	sound->Play();
	CLevel_Lobby* level = static_cast<CLevel_Lobby*>(CLevelMgr::GetInst()->GetCurrentLevel());
	if (0 <= level->GetCurPanelStartIndex() - 3)
	{
		level->SetCurPanelStartIndex(level->GetCurPanelStartIndex() - 3);
		level->UpdateSelectCookieUI();
	}
}

void PageMinusBtnPetCallBackFunc()
{
	CSound* sound = CResourceMgr::GetInst()->FindSound(L"Effect_UIBtn");
	sound->SetVolume(80.f);
	sound->Play();
	CLevel_Lobby* level = static_cast<CLevel_Lobby*>(CLevelMgr::GetInst()->GetCurrentLevel());
	if (0 <= level->GetCurPanelStartIndex() - 3)
	{
		level->SetCurPanelStartIndex(level->GetCurPanelStartIndex() - 3);
		level->UpdateSelectPetUI();
	}
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
	m_CurPanelStartIndex = 0;
	m_Resolution = CEngine::GetInst()->GetResolution();

	m_SelectCookieStr = L"Brave_Cookie";
	m_SelectPetStr = L"GoldDrop";

	LoadSoundResource();
	LoadTextureResource();
	
	CResourceMgr::GetInst()->LoadCookieInfo();
	CResourceMgr::GetInst()->LoadPetInfo();

	m_BGM = CResourceMgr::GetInst()->FindSound(L"Bgm_MainLobby");
	m_BGM->SetVolume(20.f);
	m_BGM->PlayToBGM(true);


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

	// Load Cookie Info From File
	LoadCookieList();
	LoadPetList();

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

	ButtonUI = new CButtonUI;
	ButtonUI->SetScale(ImageUI->GetTexture()->GetWidth() / 2.f, ImageUI->GetTexture()->GetHeight());
	ButtonUI->SetPos(-130, 0);
	ButtonUI->SetCallBack(&SelectCookieBtnCallBackFunc);
	ImageUI->AddChildUI(ButtonUI);

	ButtonUI = new CButtonUI;
	ButtonUI->SetScale(ImageUI->GetTexture()->GetWidth() / 2.f, ImageUI->GetTexture()->GetHeight());
	ButtonUI->SetPos(130, 0);
	ButtonUI->SetCallBack(&SelectPetBtnCallBackFunc);
	ImageUI->AddChildUI(ButtonUI);


	m_CurCookieUI = new CImageUI;
	// TODO : 나중에 파일로 기본 설정값 바꾸기
	m_CurCookieUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"Illust_Brave_Cookie"));
	m_CurCookieUI->SetScale(210.f, 240.f);
	m_CurCookieUI->SetPos(100.f, 0.f);
	PanelUI->AddChildUI(m_CurCookieUI);

	m_CurPetUI = new CImageUI;
	m_CurPetUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"Illust_Pet_GoldDrop"));
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
	ImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"NowEP_1"));
	ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
	ImageUI->SetPos(100, -50);
	PanelUI->AddChildUI(ImageUI);

	ButtonUI = new CButtonUI;
	ButtonUI->SetNormalImage(CResourceMgr::GetInst()->FindTexture(L"EpisodeMap_Normal"));
	ButtonUI->SetCallBack(&EpisodeMapBtnCallBackFunc);
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
	m_BGM->Stop();
	CGameDataMgr::GetInst()->SetCurPlayCookie(m_SelectCookieStr);
	CGameDataMgr::GetInst()->SetCurPlayPet(m_SelectPetStr);
}

void CLevel_Lobby::LoadSoundResource()
{
	CResourceMgr::GetInst()->LoadSound(L"Bgm_MainLobby", L"sound\\Bgm_MainLobby.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_GameStart", L"sound\\Effect_GameStart.wav");
	if (CResourceMgr::GetInst()->FindSound(L"Effect_UIBtn") == nullptr)
	{
		CResourceMgr::GetInst()->LoadSound(L"Effect_UIBtn", L"sound\\Effect_UIButton.wav");
	}
}

void CLevel_Lobby::LoadTextureResource()
{
	for (int i = 0; i < 10; ++i)
	{
		CResourceMgr::GetInst()->LoadTexture(L"SmallScore_" + std::to_wstring(i), L"texture\\HUD\\SmallScore_" + std::to_wstring(i) + L".png");
		CResourceMgr::GetInst()->LoadTexture(L"BigScore_" + std::to_wstring(i), L"texture\\HUD\\BigScore_" + std::to_wstring(i) + L".png");
	}

	// Cookie & Pet Select Texture
	CResourceMgr::GetInst()->CreateTextureWithAlpha(L"BlackBackgroundTex", m_Resolution.x + 1, m_Resolution.y + 1, Color(178, 0, 0, 0));
	CResourceMgr::GetInst()->LoadTexture(L"SelectCookieBG0", L"texture\\Lobby\\SelectCookieBG0.png");
	CResourceMgr::GetInst()->LoadTexture(L"SelectCookieBG1", L"texture\\Lobby\\SelectCookieBG1.png");
	CResourceMgr::GetInst()->LoadTexture(L"LeftArrow_Btn", L"texture\\Lobby\\LeftArrow_Btn.png");
	CResourceMgr::GetInst()->LoadTexture(L"RightArrow_Btn", L"texture\\Lobby\\RightArrow_Btn.png");

	// Cookie Illustration
	CResourceMgr::GetInst()->LoadTexture(L"Illust_Brave_Cookie", L"texture\\Illustration\\Illust_Brave_Cookie.png");
	CResourceMgr::GetInst()->LoadTexture(L"Illust_Angel_Cookie", L"texture\\Illustration\\Illust_Angel_Cookie.png");
	CResourceMgr::GetInst()->LoadTexture(L"Illust_Knight_Cookie", L"texture\\Illustration\\Illust_Knight_Cookie.png");
	CResourceMgr::GetInst()->LoadTexture(L"Illust_Onion_Cookie", L"texture\\Illustration\\Illust_Onion_Cookie.png");
	CResourceMgr::GetInst()->LoadTexture(L"Illust_Princess_Cookie", L"texture\\Illustration\\Illust_Princess_Cookie.png");
	CResourceMgr::GetInst()->LoadTexture(L"Illust_Zombie_Cookie", L"texture\\Illustration\\Illust_Zombie_Cookie.png");

	// Cookie Label
	CResourceMgr::GetInst()->LoadTexture(L"Label_Brave_Cookie", L"texture\\Lobby\\Label_Brave_Cookie.png");
	CResourceMgr::GetInst()->LoadTexture(L"Label_Angel_Cookie", L"texture\\Lobby\\Label_Angel_Cookie.png");
	CResourceMgr::GetInst()->LoadTexture(L"Label_Knight_Cookie", L"texture\\Lobby\\Label_Knight_Cookie.png");
	CResourceMgr::GetInst()->LoadTexture(L"Label_Onion_Cookie", L"texture\\Lobby\\Label_Onion_Cookie.png");
	CResourceMgr::GetInst()->LoadTexture(L"Label_Princess_Cookie", L"texture\\Lobby\\Label_Princess_Cookie.png");
	CResourceMgr::GetInst()->LoadTexture(L"Label_Zombie_Cookie", L"texture\\Lobby\\Label_Zombie_Cookie.png");

	// Pet Illustration
	CResourceMgr::GetInst()->LoadTexture(L"Illust_Pet_GoldDrop", L"texture\\Illustration\\Illust_Pet_GoldDrop.png");
	CResourceMgr::GetInst()->LoadTexture(L"Illust_Pet_Flowercopter", L"texture\\Illustration\\Illust_Pet_Flowercopter.png");
	CResourceMgr::GetInst()->LoadTexture(L"Illust_Pet_GingerGhost", L"texture\\Illustration\\Illust_Pet_GingerGhost.png");
	CResourceMgr::GetInst()->LoadTexture(L"Illust_Pet_FoxyBead", L"texture\\Illustration\\Illust_Pet_FoxyBead.png");
	CResourceMgr::GetInst()->LoadTexture(L"Illust_Pet_OnionFish", L"texture\\Illustration\\Illust_Pet_OnionFish.png");
	CResourceMgr::GetInst()->LoadTexture(L"Illust_Pet_GlitterBall", L"texture\\Illustration\\Illust_Pet_GlitterBall.png");

	// Pet Label
	CResourceMgr::GetInst()->LoadTexture(L"Label_Pet_GoldDrop", L"texture\\Lobby\\Label_Pet_GoldDrop.png");
	CResourceMgr::GetInst()->LoadTexture(L"Label_Pet_Flowercopter", L"texture\\Lobby\\Label_Pet_Flowercopter.png");
	CResourceMgr::GetInst()->LoadTexture(L"Label_Pet_GingerGhost", L"texture\\Lobby\\Label_Pet_GingerGhost.png");
	CResourceMgr::GetInst()->LoadTexture(L"Label_Pet_FoxyBead", L"texture\\Lobby\\Label_Pet_FoxyBead.png");
	CResourceMgr::GetInst()->LoadTexture(L"Label_Pet_OnionFish", L"texture\\Lobby\\Label_Pet_OnionFish.png");
	CResourceMgr::GetInst()->LoadTexture(L"Label_Pet_GlitterBall", L"texture\\Lobby\\Label_Pet_GlitterBall.png");

	CResourceMgr::GetInst()->LoadTexture(L"SelectButton", L"texture\\Lobby\\SelectButton.png");

	// Episode UI Texture
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

void CLevel_Lobby::SetEpisodeMapUI()
{
	
}

void CLevel_Lobby::SetSelectCookieUI()
{
	CPanelUI* PanelUI = nullptr;
	CImageUI* ImageUI = nullptr;
	CButtonUI* ButtonUI = nullptr;

	// SelectCookie Panel
	m_SelectCookiePanel = new CPanelUI;
	m_SelectCookiePanel->SetName(L"SelectCookiePanel");
	m_SelectCookiePanel->SetTexture(CResourceMgr::GetInst()->FindTexture(L"BlackBackgroundTex"));
	m_SelectCookiePanel->SetScale(m_SelectCookiePanel->GetTexture()->GetWidth(), m_SelectCookiePanel->GetTexture()->GetHeight());
	m_SelectCookiePanel->SetPos(m_Resolution.x / 2.f, m_Resolution.y / 2.f);

	PanelUI = new CPanelUI;
	PanelUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"SelectCookieBG0"));
	PanelUI->SetScale(PanelUI->GetTexture()->GetWidth(), PanelUI->GetTexture()->GetHeight());
	PanelUI->SetPos(0, 0);
	m_SelectCookiePanel->AddChildUI(PanelUI);

	ImageUI = new CImageUI;
	ImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"SelectCookieBG1"));
	ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
	ImageUI->SetPos(0, 0);
	m_SelectCookiePanel->AddChildUI(ImageUI);

	// Change SelectPage Button
	ButtonUI = new CButtonUI;
	ButtonUI->SetNormalImage(CResourceMgr::GetInst()->FindTexture(L"RightArrow_Btn"));
	ButtonUI->SetHoverImage(CResourceMgr::GetInst()->FindTexture(L"RightArrow_Btn"));
	ButtonUI->SetPos(450, 0);
	ButtonUI->SetCallBack(&PagePlusBtnCallBackFunc);
	ButtonUI->SetScale(36.f, 54.f);
	m_SelectCookiePanel->AddChildUI(ButtonUI);

	ButtonUI = new CButtonUI;
	ButtonUI->SetNormalImage(CResourceMgr::GetInst()->FindTexture(L"LeftArrow_Btn"));
	ButtonUI->SetHoverImage(CResourceMgr::GetInst()->FindTexture(L"LeftArrow_Btn"));
	ButtonUI->SetPos(-450, 0);
	ButtonUI->SetCallBack(&PageMinusBtnCallBackFunc);
	ButtonUI->SetScale(36.f, 54.f);
	m_SelectCookiePanel->AddChildUI(ButtonUI);


	// Set Cookie Profile
	for (int i = 0; i < m_vecCookieStr.size(); ++i)
	{
		wstring CookieName = m_vecCookieStr[i];

		PanelUI = new CPanelUI;
		PanelUI->SetScale(280.f, 400.f);
		PanelUI->SetPos(-280 + (PanelUI->GetScale().x * (i % 3)), 0);

		ImageUI = new CImageUI;
		ImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"Illust_" + CookieName));
		ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
		ImageUI->SetPos(0, -90);
		PanelUI->AddChildUI(ImageUI);

		ImageUI = new CImageUI;
		ImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"Label_" + CookieName));
		ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
		ImageUI->SetPos(0, 100);
		PanelUI->AddChildUI(ImageUI);

		ButtonUI = new CButtonUI;
		ButtonUI->SetNormalImage(CResourceMgr::GetInst()->FindTexture(L"SelectButton"));
		ButtonUI->SetHoverImage(CResourceMgr::GetInst()->FindTexture(L"SelectButton"));
		ButtonUI->SetScale(165, 62);
		ButtonUI->SetPos(0, 170);
		ButtonUI->SetCallBackParam(CloseSelectCookieBtnCallBackFunc, ButtonUI);
		PanelUI->AddChildUI(ButtonUI);

		m_vecCookieBtn.push_back(ButtonUI);
		m_vecCookiePanel.push_back(PanelUI);
	}

	for (int i = 0; i < 3; ++i)
	{
		m_SelectCookiePanel->AddChildUI(m_vecCookiePanel[i]);
	}

	m_SelectCookieStr = m_vecCookieStr[0];
}

void CLevel_Lobby::UpdateSelectCookieUI()
{
	for (int i = m_CurPanelStartIndex; i < m_CurPanelStartIndex + 3; ++i)
	{
		if (m_vecCookiePanel.size() <= i) break;
		m_SelectCookiePanel->UpdateChildUI(m_vecCookiePanel[i], 4 + (i % 3));
	}
}

void CLevel_Lobby::UpdateSelectPetUI()
{
	for (int i = m_CurPanelStartIndex; i < m_CurPanelStartIndex + 3; ++i)
	{
		if (m_vecPetPanel.size() <= i) break;
		m_SelectPetPanel->UpdateChildUI(m_vecPetPanel[i], 4 + (i % 3));
	}
}

void CLevel_Lobby::SetSelectPetUI()
{
	CPanelUI* PanelUI = nullptr;
	CImageUI* ImageUI = nullptr;
	CButtonUI* ButtonUI = nullptr;

	// SelectPet Panel
	m_SelectPetPanel = new CPanelUI;
	m_SelectPetPanel->SetName(L"SelectPetPanel");
	m_SelectPetPanel->SetTexture(CResourceMgr::GetInst()->FindTexture(L"BlackBackgroundTex"));
	m_SelectPetPanel->SetScale(m_SelectPetPanel->GetTexture()->GetWidth(), m_SelectPetPanel->GetTexture()->GetHeight());
	m_SelectPetPanel->SetPos(m_Resolution.x / 2.f, m_Resolution.y / 2.f);

	PanelUI = new CPanelUI;
	PanelUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"SelectCookieBG0"));
	PanelUI->SetScale(PanelUI->GetTexture()->GetWidth(), PanelUI->GetTexture()->GetHeight());
	PanelUI->SetPos(0, 0);
	m_SelectPetPanel->AddChildUI(PanelUI);

	ImageUI = new CImageUI;
	ImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"SelectCookieBG1"));
	ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
	ImageUI->SetPos(0, 0);
	m_SelectPetPanel->AddChildUI(ImageUI);

	// Change SelectPage Button
	ButtonUI = new CButtonUI;
	ButtonUI->SetNormalImage(CResourceMgr::GetInst()->FindTexture(L"RightArrow_Btn"));
	ButtonUI->SetHoverImage(CResourceMgr::GetInst()->FindTexture(L"RightArrow_Btn"));
	ButtonUI->SetPos(450, 0);
	ButtonUI->SetCallBack(&PagePlusBtnPetCallBackFunc);
	ButtonUI->SetScale(36.f, 54.f);
	m_SelectPetPanel->AddChildUI(ButtonUI);

	ButtonUI = new CButtonUI;
	ButtonUI->SetNormalImage(CResourceMgr::GetInst()->FindTexture(L"LeftArrow_Btn"));
	ButtonUI->SetHoverImage(CResourceMgr::GetInst()->FindTexture(L"LeftArrow_Btn"));
	ButtonUI->SetPos(-450, 0);
	ButtonUI->SetCallBack(&PageMinusBtnPetCallBackFunc);
	ButtonUI->SetScale(36.f, 54.f);
	m_SelectPetPanel->AddChildUI(ButtonUI);


	// Set Cookie Profile
	for (int i = 0; i < m_vecPetStr.size(); ++i)
	{
		wstring PetName = m_vecPetStr[i];

		PanelUI = new CPanelUI;
		PanelUI->SetScale(280.f, 400.f);
		PanelUI->SetPos(-280 + (PanelUI->GetScale().x * (i % 3)), 0);

		ImageUI = new CImageUI;
		ImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"Illust_Pet_" + PetName));
		ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
		ImageUI->SetPos(0, -90);
		PanelUI->AddChildUI(ImageUI);

		ImageUI = new CImageUI;
		ImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"Label_Pet_" + PetName));
		ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
		ImageUI->SetPos(0, 100);
		PanelUI->AddChildUI(ImageUI);

		ButtonUI = new CButtonUI;
		ButtonUI->SetNormalImage(CResourceMgr::GetInst()->FindTexture(L"SelectButton"));
		ButtonUI->SetHoverImage(CResourceMgr::GetInst()->FindTexture(L"SelectButton"));
		ButtonUI->SetScale(165, 62);
		ButtonUI->SetPos(0, 170);
		ButtonUI->SetCallBackParam(CloseSelectPetBtnCallBackFunc, ButtonUI);
		PanelUI->AddChildUI(ButtonUI);

		m_vecPetBtn.push_back(ButtonUI);
		m_vecPetPanel.push_back(PanelUI);
	}

	for (int i = 0; i < 3; ++i)
	{
		m_SelectPetPanel->AddChildUI(m_vecPetPanel[i]);
	}

	m_SelectPetStr = m_vecPetStr[0];
}

void CLevel_Lobby::FindSelectCookieByBtn(CButtonUI* _btn)
{
	for (int i = 0; i < m_vecCookieBtn.size(); ++i)
	{
		if (m_vecCookieBtn[i] == _btn)
		{
			m_SelectCookieStr = m_vecCookieStr[i];
			m_CurCookieUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"Illust_" + m_vecCookieStr[i]));
			CGameDataMgr::GetInst()->SetCurPlayCookie(m_SelectCookieStr);
			m_CurCookieUI->SetScale(210.f, 240.f);
			return;
		}
	}
}

void CLevel_Lobby::FindSelectPetByBtn(CButtonUI* _btn)
{
	for (int i = 0; i < m_vecPetBtn.size(); ++i)
	{
		if (m_vecPetBtn[i] == _btn)
		{
			m_SelectPetStr = m_vecPetStr[i];
			m_CurPetUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"Illust_Pet_" + m_vecPetStr[i]));
			CGameDataMgr::GetInst()->SetCurPlayPet(m_SelectPetStr);
			m_CurPetUI->SetScale(130.f, 130.f);
			return;
		}
	}
}

void CLevel_Lobby::SpawnSelectCookieUI()
{
	if (m_SelectingCookie == false)
	{
		m_CurPanelStartIndex = 0;
		SetSelectCookieUI();
		m_SelectingCookie = true;
		AddObject(LAYER_TYPE::UI, m_SelectCookiePanel);
	}
}

void CLevel_Lobby::SpawnSelectPetUI()
{
	if (m_SelectingCookie == false)
	{
		m_CurPanelStartIndex = 0;
		SetSelectPetUI();
		m_SelectingCookie = true;
		AddObject(LAYER_TYPE::UI, m_SelectPetPanel);
	}
}

void CLevel_Lobby::DeleteSelectCookieUI()
{
	if (m_SelectingCookie == true)
	{
		m_SelectingCookie = false;
		m_SelectCookiePanel->Destroy();
		m_vecCookiePanel.clear();
		m_vecCookieBtn.clear();
	}
}

void CLevel_Lobby::DeleteSelectPetUI()
{
	if (m_SelectingCookie == true)
	{
		m_SelectingCookie = false;
		m_SelectPetPanel->Destroy();
		m_vecPetPanel.clear();
		m_vecPetBtn.clear();
	}
}

void CLevel_Lobby::LoadCookieList()
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"CookieInfo.info";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"r");

	if (nullptr == pFile) { return; }

	wchar_t szReadBuff[256] = {};

	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		wstring strRead = szReadBuff;

		if (strRead == L"[COOKIE_COUNT]")
		{
			int Count = 0;
			fwscanf_s(pFile, L"%d", &Count);

			for (int i = 0; i < Count; ++i)
			{
				do { fwscanf_s(pFile, L"%s", szReadBuff, 256); } while (wcscmp(szReadBuff, L"[COOKIE_NAMESTR]"));
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				wstring strRead = szReadBuff;

				m_vecCookieStr.push_back(strRead);
			}
		}
	}
	fclose(pFile);
}

void CLevel_Lobby::LoadPetList()
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"PetInfo.info";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"r");

	if (nullptr == pFile) { return; }

	wchar_t szReadBuff[256] = {};

	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		wstring strRead = szReadBuff;

		if (strRead == L"[PET_COUNT]")
		{
			int Count = 0;
			fwscanf_s(pFile, L"%d", &Count);

			for (int i = 0; i < Count; ++i)
			{
				do { fwscanf_s(pFile, L"%s", szReadBuff, 256); } while (wcscmp(szReadBuff, L"[PET_NAMESTR]"));
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				wstring strRead = szReadBuff;

				m_vecPetStr.push_back(strRead);
			}
		}
	}
	fclose(pFile);
}