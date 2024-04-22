#include "pch.h"
#include "CLevel_Game.h"

#include "CCollisionMgr.h"
#include "CSoundMgr.h"
#include "CDbgRenderMgr.h"
#include "CGameDataMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CStageMgr.h"
#include "CJellyMgr.h"
#include "CTaskMgr.h"

#include "CEngine.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CPet.h"
#include "CBackground.h"
#include "CRigidBody.h"
#include "CPlatform.h"
#include "CObstacle.h"
#include "CStage.h"
#include "CJelly.h"
#include "CSound.h"
#include "CPanelUI.h"
#include "CImageUI.h"
#include "CButtonUI.h"
#include "CScoreUI.h"

// TODO : 테스트용. 나중에 지워도 되는 헤더들
#include "CCollider.h"
#include "CAnimator.h"

void GameOverBtnCallBackFunc()
{
	CSound* sound = CResourceMgr::GetInst()->FindSound(L"Effect_UIBtn");
	sound->SetVolume(80.f);
	sound->Play();
	
	CLevelMgr::GetInst()->ChangeLevel(LEVEL_TYPE::LOBBY);
}

CLevel_Game::CLevel_Game()
	: m_Cookie(nullptr)
	, m_Pet(nullptr)
	, m_ActingPosX(0)
	, m_DeletePosX(0)
	, m_PostStageStartPosX(0)
	, m_DestinationPosX(0)
	, m_BGM(nullptr)
	, m_CookieStateAction(0)
	, m_PrevStage(nullptr)
	, m_PostStage(nullptr)
	, m_CurStage(nullptr)
	, m_Resolution(0)
	, m_GameOver(false)
	, m_BtnJump(nullptr)
	, m_BtnSlide(nullptr)
	, m_MarkMiniMap(nullptr)
	
{
	
}

CLevel_Game::~CLevel_Game()
{
	Safe_Del_Arr(m_BTAlphabet);
}

void CLevel_Game::begin()
{
	CLevel::begin();

	m_ActingPosX = 0;
	m_DeletePosX = m_Resolution.x;

	// Timer Setting
	CTimeMgr::GetInst()->AddTimer(0.25f, [this]() {
		m_LogPos = m_Cookie->GetPos();
		}, true);

	CTimeMgr::GetInst()->AddTimer(0.1f, [this]() {
		if (!CGameDataMgr::GetInst()->IsCookieDead()) CGameDataMgr::GetInst()->AddScore(10);
		else CGameDataMgr::GetInst()->AddScore(0);
		}, true);

	CTimeMgr::GetInst()->AddTimer(3.f, [this]() {
		CGameDataMgr::GetInst()->DeductHP(5);
		}, true);

	m_BGM = CResourceMgr::GetInst()->FindSound(L"Bgm_MainGame");
	m_BGM->SetVolume(50.f);
	m_BGM->PlayToBGM(true);
}



void CLevel_Game::tick()
{
	// Editor Level 진입
	if (CKeyMgr::GetInst()->GetKeyState(KEY::E) == KEY_STATE::TAP)
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}

	if (CGameDataMgr::GetInst()->IsCookieDead() == true)
	{
		m_Cookie->SetSpeed(0);
		m_Pet->SetSpeed(0);
		
		vector<CObject*> BG = GetObjectsByLayerType(LAYER_TYPE::BACKGROUND);
		for (size_t i = 0; i < BG.size(); ++i)
		{
			BG[i]->SetSpeed(0);
		}

		CCollisionMgr::GetInst()->CollisionUnCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::OBSTACLE);
		CCollisionMgr::GetInst()->CollisionUnCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::JELLY);
		
		m_BGM->Stop();

		// TODO : 게임오버 UI창 띄우기
		CTimeMgr::GetInst()->AddTimer(2.0f, [this]() {
			ShowGameOverUI();
			m_GameOver = true;
			}, false);

	}

	//if (m_GameOver == true)
	//{
	//	m_BGM->Stop();

	//	// TODO : 게임오버 UI창 띄우기
	//	CTimeMgr::GetInst()->AddTimer(2.0f, [this]() {
	//		ShowGameOverUI();
	//		}, false);
	//	
	//}

	CLevel::tick();

	if (m_Cookie == nullptr)
		return;

	UINT EP = (UINT)m_CurStage->GetEPType();
	UINT STG = (UINT)m_CurStage->GetSTGType();
	
	CCamera::GetInst()->SetCameraFocus();

	float StandardPosX = m_Cookie->GetPos().x;
	m_ActingPosX = StandardPosX + 800.f;
	m_DeletePosX = StandardPosX - m_Resolution.x * 0.5f;

	// Cookie Debug Info
	
	DbgObjInfo CurCoinInfo = { CCamera::GetInst()->GetRealPos(Vec2D(600, 50)), 0, 
								L"Coin : " + std::to_wstring(CGameDataMgr::GetInst()->GetCurGameCoin()) };
	

	DbgObjInfo HighScoreInfo = { CCamera::GetInst()->GetRealPos(Vec2D(1100, 100)), 0,
								L"High Score : " + std::to_wstring(CGameDataMgr::GetInst()->GetHighScore()) };

	DbgObjInfo CurScoreInfo = { CCamera::GetInst()->GetRealPos(Vec2D(1100, 120)), 0,
								L"Current Score : " + std::to_wstring(CGameDataMgr::GetInst()->GetCurScore()) };

	DbgObjInfo CurHPInfo = { CCamera::GetInst()->GetRealPos(Vec2D(100, 100)), 0,
								L"HP : " + std::to_wstring(CGameDataMgr::GetInst()->GetCurHP()) + L"/" + std::to_wstring(CGameDataMgr::GetInst()->GetMaxHP())
								+ L" (" + std::to_wstring(CGameDataMgr::GetInst()->GetRateHP()) + L"%)" };

	CDbgRenderMgr::GetInst()->AddDbgObjInfo(CurCoinInfo);
	CDbgRenderMgr::GetInst()->AddDbgObjInfo(HighScoreInfo);
	CDbgRenderMgr::GetInst()->AddDbgObjInfo(CurScoreInfo);
	CDbgRenderMgr::GetInst()->AddDbgObjInfo(CurHPInfo);

	PrintCookieLog();

	// ================================================
	//					Update HUD
	// ================================================
	// 
	// Jump & Slide Button State Check
	if (KEY_TAP(KEY::SPACE) || KEY_PRESSED(KEY::SPACE))
	{
		m_BtnJump->SetButtonState(1);
	}
	else if (KEY_RELEASED(KEY::SPACE))
	{
		m_BtnJump->SetButtonState(0);
	}

	if (KEY_TAP(KEY::DOWN) || KEY_PRESSED(KEY::DOWN))
	{
		m_BtnSlide->SetButtonState(1);
	}
	else if (KEY_RELEASED(KEY::DOWN))
	{
		m_BtnSlide->SetButtonState(0);
	}

	// BonusTime Update
	if (CGameDataMgr::GetInst()->IsBTEditing())
	{
		for (int i = 0; i < 9; ++i)
		{
			if (CGameDataMgr::GetInst()->CheckAlphabetOn(i))
			{
				m_BTAlphabet[i]->SetTexture(CResourceMgr::GetInst()->FindTexture(L"BonusTime_" + std::to_wstring(i)));
			}
		}
		CGameDataMgr::GetInst()->DoneBTEditing();
	}
	
	// MiniMap Update
	float RunRateStandard = m_Cookie->GetPos().x - (m_DestinationPosX - m_CurStage->GetSTGLength());
	float RunRate = ( RunRateStandard / m_CurStage->GetSTGLength()) * 100.f;
	m_MarkMiniMap->SetPos(-80.f + RunRate * 1.5f, m_MarkMiniMap->GetPos().y);

	// HP Update
	m_HeartGauge->SetScale(CGameDataMgr::GetInst()->GetRateHP() * 7.5f, m_HeartGauge->GetScale().y);
	m_HeartGaugeEffect->SetPos(m_HeartGauge->GetScale().x, 0);
	if (CGameDataMgr::GetInst()->GetRateHP() <= 20.f)
	{
		m_WarningEffect = true;
	}
	else
	{
		m_WarningEffect = false;
	}

	if (m_WarningEffect && !m_EffectPlaying)
	{
		m_EffectPlaying = true;
		CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::DAMAGE_FADE_IN, 1.f);
		CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::DAMAGE_FADE_OUT, 1.f);
		CTimeMgr::GetInst()->AddTimer(2.f, [this]() {
			m_EffectPlaying = false;
			}, false);
	}

	// Coin Score Update
	if (CGameDataMgr::GetInst()->IsCoinEditing())
	{
		m_vecScore.clear();

		// Setting Digit
		int coin = CGameDataMgr::GetInst()->GetCurGameCoin();
		while (true)
		{
			m_vecScore.push_back(coin % 10);
			if (coin / 10 < 1) break;
			else
			{
				coin /= 10;
			}
		}
		int digit = m_vecScore.size();

		// Add Child UI
		const vector<CUI*>& ScoreUI = m_CoinScoreUI->GetChildUI();         // [0]은 제외!
		int count = ScoreUI.size();
		for (int i = 0; i < digit - (count - 1); ++i)
		{
			m_CoinScoreUI->AddChildUI(ScoreUI[1]->Clone());
		}

		// Set Score at UI
		for (int i = 0; i < digit; ++i)
		{
			CScoreUI* pScoreUI = static_cast<CScoreUI*>(ScoreUI[1 + i]);
			pScoreUI->SetSmallScore(m_vecScore[digit - 1 - i]);
		}

		// Set Pos All UI
		for (int i = 1; i < ScoreUI.size(); ++i)
		{
			ScoreUI[i]->SetPos(30 + ScoreUI[i]->GetTexture()->GetWidth() * i, 0);
		}

		CGameDataMgr::GetInst()->DoneCoinEditing();
	}


	// Cur Score Update
	if (CGameDataMgr::GetInst()->IsScoreEditing())
	{
		m_vecScore.clear();

		// Setting Digit
		int score = CGameDataMgr::GetInst()->GetCurScore();
		while (true)
		{
			m_vecScore.push_back(score % 10);
			if (score / 10 < 1) break;
			else
			{
				score /= 10;
			}
		}
		int digit = m_vecScore.size();

		// Add Child UI
		const vector<CUI*>& ScoreUI = m_CurScoreUI->GetChildUI();         // [0]은 제외!
		int count = ScoreUI.size();
		for (int i = 0; i < digit - count; ++i)
		{
			m_CurScoreUI->AddChildUI(ScoreUI[0]->Clone());
		}

		// Set Score at UI
		for (int i = 0; i < digit; ++i)
		{
			CScoreUI* pScoreUI = static_cast<CScoreUI*>(ScoreUI[i]);
			pScoreUI->SetBigScore(m_vecScore[digit - 1 - i]);
		}

		// Set Pos All UI
		for (int i = 0; i < ScoreUI.size(); ++i)
		{
			float StartPosX = (8 - digit) * (ScoreUI[i]->GetTexture()->GetWidth());
			ScoreUI[i]->SetPos(StartPosX + (ScoreUI[i]->GetTexture()->GetWidth() * i), 0.f);
		}

		CGameDataMgr::GetInst()->DoneScoreEditing();
	}

	if (CGameDataMgr::GetInst()->GetHighScore() < CGameDataMgr::GetInst()->GetCurScore())
	{
		const vector<CUI*>& ScoreUI = m_HighScoreUI->GetChildUI();
		for (int i = 0; i < ScoreUI.size(); ++i)
		{
			if (i == 0)
			{
				ScoreUI[i]->SetTexture(CResourceMgr::GetInst()->FindTexture(L"Best"));
				ScoreUI[i]->SetScale(ScoreUI[i]->GetTexture()->GetWidth(), ScoreUI[i]->GetTexture()->GetHeight());
				ScoreUI[i]->SetPos(250.f, 50.f);
			}
			else
			{
				ScoreUI[i]->SetTexture(nullptr);
			}
		}
	}
	// ===================================================


	// Obstacle Animation Play
	const vector<CObject*>& vecObs = GET_CUR_LEVEL->GetObjectsByLayerType(LAYER_TYPE::OBSTACLE);
	CObstacle* obs = nullptr;
	float tPosX = 0;

	for (size_t i = 0; i < vecObs.size(); ++i)
	{
		obs = static_cast<CObstacle*>(vecObs[i]);	
		tPosX = vecObs[i]->GetPos().x;
		if (tPosX <= m_ActingPosX)
		{
			if (obs->GetActed() == true) continue;

			if (obs->GetOBSType() == OBS_TYPE::DBJUMP_UP || obs->GetOBSType() == OBS_TYPE::JUMP_UP)
			{
				wstring AnimName = L"EP" + std::to_wstring(EP + 1)
					+ L"_STG" + std::to_wstring(STG + 1)
					+ L"_OBS" + std::to_wstring((UINT)obs->GetOBSType());

				vecObs[i]->GetAnimator()->ChangePlayingAnim(AnimName, false);
				obs->GetEffectSound()->SetVolume(80.f);
				obs->GetEffectSound()->Play();
				obs->SetActed(true);
			}
			else if (obs->GetOBSType() == OBS_TYPE::JUMP_DOWN || obs->GetOBSType() == OBS_TYPE::DBJUMP_DOWN)
			{
				if (600.f <= obs->GetPos().y)
				{
					obs->SetPos(obs->GetPos().x, 600.f);
					obs->GetEffectSound()->SetVolume(80.f);
					obs->GetEffectSound()->Play();
					obs->SetActed(true);
				}
				else
				{
					obs->SetPos(Vec2D(obs->GetPos().x, obs->GetPos().y + (600 * DT * 4.f)));
					Vec2D check = obs->GetPos();
					int a = 0;
				}
			}
		}
	}

	if (m_JellyAttract == true)
	{
		CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PET, LAYER_TYPE::JELLY);

		const vector<CObject*>& vecJelly = GET_CUR_LEVEL->GetObjectsByLayerType(LAYER_TYPE::JELLY);
		CJelly* Jelly = nullptr;
		float tPosX = 0;

		for (size_t i = 0; i < vecJelly.size(); ++i)
		{
			Jelly = static_cast<CJelly*>(vecJelly[i]);
			tPosX = vecJelly[i]->GetPos().x;
			if (m_Cookie->GetPos().x < tPosX && tPosX <= m_ActingPosX)
			{
				float MoveDistanceX = (m_Pet->GetPos().x - Jelly->GetPos().x) * DT * 2.f;
				float MoveDistanceY = (m_Pet->GetPos().y - Jelly->GetPos().y) * DT * 2.f;
				Jelly->SetPos(Jelly->GetPos().x + MoveDistanceX, Jelly->GetPos().y + MoveDistanceY);
			}	
		}
	}
	else
	{
		CCollisionMgr::GetInst()->CollisionUnCheck(LAYER_TYPE::PET, LAYER_TYPE::JELLY);
	}
	

	// Delete Passed Stage Object
	for (int i = 0; i < (UINT)LAYER_TYPE::UI; ++i)
	{
		const vector<CObject*>& vecObj = GET_CUR_LEVEL->GetObjectsByLayerType(static_cast<LAYER_TYPE>(i));

		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			float tPosX = 0.0f;
			if (vecObj[j]->GetLayerType() == LAYER_TYPE::BACKGROUND)
			{
				tPosX = vecObj[j]->GetPos().x + vecObj[j]->GetScale().x * 2.25f;
			}
			else
			{
				tPosX = vecObj[j]->GetPos().x + vecObj[j]->GetScale().x;
			}

			if (tPosX <= m_DeletePosX)
			{
				vecObj[j]->Destroy();
			}
		}
	}


	// Cookie's Complex State Check
	CCollider* CookieCol = m_Cookie->GetComponent<CCollider>();

	if (m_Cookie->CheckCookieState(COOKIE_COMPLEX_STATE::INVINCIBLE))
	{
		DbgObjInfo info = { CCamera::GetInst()->GetRealPos(Vec2D(300, 50)), 0, L"INVINCIBLE ON" };
		CDbgRenderMgr::GetInst()->AddDbgObjInfo(info);

		if (!(m_CookieStateAction & (int)COOKIE_COMPLEX_STATE::INVINCIBLE))
		{
			m_CookieStateAction |= (int)COOKIE_COMPLEX_STATE::INVINCIBLE;

			CTimeMgr::GetInst()->AddTimer(2.3f, [this]() {
				m_Cookie->TurnOffCookieState(COOKIE_COMPLEX_STATE::INVINCIBLE);
				LOG(LOG_TYPE::DBG_LOG, L"INVINCIBLE OFF");
				m_CookieStateAction &= ~(int)COOKIE_COMPLEX_STATE::INVINCIBLE;
				}, false);
		}
	}
	if (m_Cookie->CheckCookieState(COOKIE_COMPLEX_STATE::GIANT))
	{
		DbgObjInfo info = { CCamera::GetInst()->GetRealPos(Vec2D(300, 70)), 0, L"GIANT ON" };
		CDbgRenderMgr::GetInst()->AddDbgObjInfo(info);

		if (!(m_CookieStateAction & (int)COOKIE_COMPLEX_STATE::GIANT))
		{
			if (m_CookieStateAction & (int)COOKIE_COMPLEX_STATE::INVINCIBLE)
			{
				m_Cookie->SetScale(m_Cookie->GetScale() - (m_Cookie->GetScale() * DT * 4.f));
				CookieCol->SetScale(CookieCol->GetScale() - (CookieCol->GetScale() * DT * 4.f));

				if (m_Cookie->GetScale() < m_Cookie->GetDefaultScale())
				{
					m_Cookie->SetScale(m_Cookie->GetDefaultScale());
					CookieCol->SetScale(m_Cookie->GetColliderDefaultScale());
					m_Cookie->TurnOffCookieState(COOKIE_COMPLEX_STATE::GIANT);
				}
			}
			else
			{
				m_CookieStateAction |= (int)COOKIE_COMPLEX_STATE::GIANT;
				CResourceMgr::GetInst()->FindSound(L"Effect_SmallToBig")->Play();
			}
		}
		else
		{
			if (m_Cookie->GetScale() < m_Cookie->GetDefaultScale() * 2.f)
			{
				m_Cookie->GetComponent<CRigidBody>()->SetGiant(true);
				m_Cookie->SetScale(m_Cookie->GetScale() + (m_Cookie->GetScale() * DT * 4.f));
				CookieCol->SetScale(CookieCol->GetScale() + (CookieCol->GetScale() * DT * 4.f));
			}
			else if (m_Cookie->GetDefaultScale() * 2.f < m_Cookie->GetScale())
			{
				m_Cookie->SetScale(m_Cookie->GetDefaultScale() * 2.f);
				CookieCol->SetScale(m_Cookie->GetColliderDefaultScale() * 2.f);

				CTimeMgr::GetInst()->AddTimer(2.3f, [this, &CookieCol]() {
					m_Cookie->GetComponent<CRigidBody>()->SetGiant(false);
					m_Cookie->TurnOnCookieState(COOKIE_COMPLEX_STATE::INVINCIBLE);
					CResourceMgr::GetInst()->FindSound(L"Effect_BigToSmall")->Play();
					m_CookieStateAction &= ~(int)COOKIE_COMPLEX_STATE::GIANT;
					LOG(LOG_TYPE::DBG_LOG, L"GIANT OFF");
					}, false);
			}
		}
	}
	if (m_Cookie->CheckCookieState(COOKIE_COMPLEX_STATE::BOOST))
	{
		DbgObjInfo info = { CCamera::GetInst()->GetRealPos(Vec2D(300, 90)), 0, L"BOOST ON" };
		CDbgRenderMgr::GetInst()->AddDbgObjInfo(info);

		if (!(m_CookieStateAction & (int)COOKIE_COMPLEX_STATE::BOOST))
		{
			m_CookieStateAction |= (int)COOKIE_COMPLEX_STATE::BOOST;
			m_Cookie->ChangeCookieFSMState(L"Dash");
			m_Pet->ChangePetFSMState(L"Dash");
			m_Cookie->SetSpeed(m_Cookie->GetSpeed() * 1.75f);
			m_Pet->SetSpeed(m_Pet->GetSpeed() * 1.75f);

			CTimeMgr::GetInst()->AddTimer(2.3f, [this]() {
				m_Cookie->SetSpeed(COOKIE_DEFAULT_SPEED);
				m_Pet->SetSpeed(COOKIE_DEFAULT_SPEED);
				m_Cookie->TurnOnCookieState(COOKIE_COMPLEX_STATE::INVINCIBLE);
				m_Cookie->TurnOffCookieState(COOKIE_COMPLEX_STATE::BOOST);
				m_Cookie->ChangeCookieFSMState(L"Run");
				m_Pet->ChangePetFSMState(L"Run");
				LOG(LOG_TYPE::DBG_LOG, L"BOOST OFF");
				m_CookieStateAction &= ~(int)COOKIE_COMPLEX_STATE::BOOST;
				}, false);
		}
	}
	if (m_Cookie->CheckCookieState(COOKIE_COMPLEX_STATE::ATTRACT))
	{
		if (!m_Pet->CheckPetFSMState(L"Attract"))
		{
			m_JellyAttract = true;
			m_Pet->ChangePetFSMState(L"Attract");

			CTimeMgr::GetInst()->AddTimer(3.f, [this]() {
				m_Pet->ChangePetFSMState(L"Run");
				m_Cookie->TurnOffCookieState(COOKIE_COMPLEX_STATE::ATTRACT);
				m_JellyAttract = false;
				}, false);
		}
	}
	
	// Stage Change Check
	if (m_PostStageStartPosX < StandardPosX + m_Resolution.x)
	{
 		m_PrevStage = m_CurStage;
		CStageMgr::GetInst()->ChangeNextStage();
		m_PostStage = CStageMgr::GetInst()->GetCurrentStage();
		
		// Static Object 배치
		for (int i = 0; i < 3; i++)
		{
			vector<StageSTObjInfo>& vecStageInfo = m_PostStage->m_vecSTObjInfo[i];
			vector<StageSTObjInfo>::iterator iter = vecStageInfo.begin();

			for (; iter < vecStageInfo.end(); ++iter)
			{
				SpawnStageSTObject(*iter);
			}
		}

		// Dynamic Object 배치
		vector<StageDNObjInfo>& vecStageInfo = m_PostStage->m_vecDNObjInfo;
		vector<StageDNObjInfo>::iterator iter = vecStageInfo.begin();

		for (; iter < vecStageInfo.end(); ++iter)
		{
			SpawnStageDNObject(*iter);
		}

		m_PostStageStartPosX += m_PostStage->GetSTGLength();
	}

	if (m_PrevStage != nullptr && m_PostStageStartPosX - m_PostStage->GetSTGLength() < StandardPosX)
	{
		m_PrevStage->Exit();

		m_CurStage = m_PostStage;
		m_DestinationPosX += m_CurStage->GetSTGLength();
		m_CurStage->Enter();
		
		m_PrevStage = nullptr;
		m_PostStage = nullptr;
	}


	// Cookie 낙사 체크
	if (m_Resolution.y + (m_Resolution.y / 2.f) < m_Cookie->GetPos().y)
	{
		CGameDataMgr::GetInst()->DeductHP(10000);
	}
}


void CLevel_Game::Enter()
{
	m_Resolution = CEngine::GetInst()->GetResolution();
	
	LoadSoundResource();
	LoadTextureResource();
	SetHUD();
	
	// 현재 스테이지 맵 데이터 불러오기
	CStageMgr::GetInst()->SetStartStage(EPISODE_TYPE::EP1);
	m_CurStage = CStageMgr::GetInst()->GetCurrentStage();
	m_CurStage->LoadSTObjectsFromFile();

	CJellyMgr::GetInst()->LoadJellyInfo();
	m_CurStage->LoadDNObjectsFromFile();
	m_PostStage = m_CurStage;

	// Static Object 배치
	for (int i = 0; i < 3; i++)
	{
		vector<StageSTObjInfo>& vecStageInfo = m_CurStage->m_vecSTObjInfo[i];
		vector<StageSTObjInfo>::iterator iter = vecStageInfo.begin();

		for (; iter < vecStageInfo.end(); ++iter)
		{
			SpawnStageSTObject(*iter);
		}
	}

	// Dynamic Object 배치
	vector<StageDNObjInfo>& vecStageInfo = m_CurStage->m_vecDNObjInfo;
	vector<StageDNObjInfo>::iterator iter = vecStageInfo.begin();

	for (; iter < vecStageInfo.end(); ++iter)
	{
		SpawnStageDNObject(*iter);
	}

	CObject* pObject = new CPlayer;
	pObject->SetName(L"Player");
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObject);
	pPlayer->SetCurCookie(CGameDataMgr::GetInst()->GetCurPlayCookie());
	pPlayer->SetPos(COOKIE_DEFAULT_POSX, COOKIE_DEFAULT_POSY);
	pPlayer->SetScale(pPlayer->GetCurCookie()._frmSize.x, pPlayer->GetCurCookie()._frmSize.y);
	pPlayer->SetSpeed(COOKIE_DEFAULT_SPEED);

	m_Cookie = pPlayer;
	CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::SPAWN_OBJECT, (DWORD_PTR)LAYER_TYPE::PLAYER, (DWORD_PTR)pObject });

	pObject = new CPet;
	pObject->SetName(L"Pet");
	CPet* pPet = dynamic_cast<CPet*>(pObject);
	pPet->SetCurPet(CGameDataMgr::GetInst()->GetCurPlayPet());
	pPet->SetPos(PET_DEFAULT_POSX, PET_DEFAULT_POSY);
	pPet->SetScale(pPet->GetCurPet()._frmSize.x, pPet->GetCurPet()._frmSize.y);
	pPet->SetSpeed(400.f);

	m_Pet = pPet;
	CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::SPAWN_OBJECT, (DWORD_PTR)LAYER_TYPE::PET, (DWORD_PTR)pObject });
	
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::OBSTACLE);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::JELLY);

	m_PostStageStartPosX = m_CurStage->GetSTGLength();
	m_DestinationPosX = m_CurStage->GetSTGLength();
}

void CLevel_Game::Exit()
{
	m_BGM->Stop();
	m_GameOver = false;
	CGameDataMgr::GetInst()->SaveToFile();
	CGameDataMgr::GetInst()->ResetForGame();

	for (UINT i = 0; i < (UINT)LAYER_TYPE::UI; ++i)
	{
		vector<CObject*> vecObjects = GetObjectsByLayerType(static_cast<LAYER_TYPE>(i));
		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			vecObjects[j]->Destroy();
		}
	}
}

void CLevel_Game::SetHUD()
{
	CPanelUI*	pPanelUI = nullptr;
	CButtonUI*	pButtonUI = nullptr;
	CImageUI*	pImageUI = nullptr;
	CScoreUI*   pScoreUI = nullptr;

	// Jump & Slide UI
	pButtonUI = new CButtonUI;
	pButtonUI->SetNormalImage(CResourceMgr::GetInst()->FindTexture(L"Jump"));
	pButtonUI->SetHoverImage(CResourceMgr::GetInst()->FindTexture(L"Jump_Dim"));
	pButtonUI->SetScale(164.5f, 124.f);
	pButtonUI->SetPos(130.f, m_Resolution.y - 100.f);
	m_BtnJump = pButtonUI;
	AddObject(LAYER_TYPE::UI, m_BtnJump);

	pButtonUI = new CButtonUI;
	pButtonUI->SetNormalImage(CResourceMgr::GetInst()->FindTexture(L"Slide"));
	pButtonUI->SetHoverImage(CResourceMgr::GetInst()->FindTexture(L"Slide_Dim"));
	pButtonUI->SetScale(164.5f, 124.f);
	pButtonUI->SetPos(m_Resolution.x - 130.f, m_Resolution.y - 100.f);
	m_BtnSlide = pButtonUI;
	AddObject(LAYER_TYPE::UI, m_BtnSlide);


	// HP UI
	pPanelUI = new CPanelUI;
	pPanelUI->SetScale(Vec2D(750.f, 30.f));
	pPanelUI->SetPos(Vec2D(500.f, 100.f));
	pPanelUI->SetTexture(CResourceMgr::GetInst()->CreateTextureWithAlpha(L"HP_Panel", 800, 50, Color(160, 0, 0, 0)));

	pImageUI = new CImageUI;
	pImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"HeartGauge"));
	pImageUI->SetScale(pImageUI->GetTexture()->GetWidth(), pImageUI->GetTexture()->GetHeight());
	pImageUI->SetPos(-375.f, 0.f);
	pImageUI->SetDecreaseUI(true);
	pPanelUI->AddChildUI(pImageUI);
	m_HeartGauge = pImageUI;

	pImageUI = new CImageUI;
	pImageUI->AddAnimator(L"HUD_HeartGaugeEffect", L"animation\\HUD_HeartGaugeEffect.anim", true);
	pImageUI->SetPos(m_HeartGauge->GetScale().x, 0.f);
	pImageUI->SetScale(36.f, 44.f);
	m_HeartGaugeEffect = pImageUI;
	m_HeartGauge->AddChildUI(pImageUI);

	pImageUI = new CImageUI;
	pImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"HeartLife"));
	pImageUI->SetScale(pImageUI->GetTexture()->GetWidth(), pImageUI->GetTexture()->GetWidth());
	pImageUI->SetPos(-375.f, 0.f);
	pPanelUI->AddChildUI(pImageUI);

	AddObject(LAYER_TYPE::UI, pPanelUI);


	// BonusTime UI
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_0", L"texture\\HUD\\BonusTime_B.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_1", L"texture\\HUD\\BonusTime_O.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_2", L"texture\\HUD\\BonusTime_N.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_3", L"texture\\HUD\\BonusTime_U.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_4", L"texture\\HUD\\BonusTime_S.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_5", L"texture\\HUD\\BonusTime_T.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_6", L"texture\\HUD\\BonusTime_I.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_7", L"texture\\HUD\\BonusTime_M.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_8", L"texture\\HUD\\BonusTime_E.png");

	for (int i = 0; i < 9; ++i)
	{
		pImageUI = new CImageUI;
		pImageUI->SetScale(42.f, 46.f);
		pImageUI->SetPos(-137 + (310.f / 9 + 2) * i, 0.f);         // TODO : 공식 수정 예정
		m_BTAlphabet[i] = pImageUI;
	}

	pImageUI = new CImageUI;
	pImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"BonusTime_BG"));
	pImageUI->SetScale(pImageUI->GetTexture()->GetWidth(), pImageUI->GetTexture()->GetHeight());
	pImageUI->SetPos(30.f + pImageUI->GetScale().x / 2.f, 30.f);
	for (int i = 0; i < 9; ++i)
	{
		pImageUI->AddChildUI(m_BTAlphabet[i]);
	}

	AddObject(LAYER_TYPE::UI, pImageUI);
	
	
	// Minimap UI
	pImageUI = new CImageUI;
	pImageUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"MiniMap_Mark", L"texture\\HUD\\MiniMap_Mark.png"));
	pImageUI->SetScale(pImageUI->GetTexture()->GetWidth(), pImageUI->GetTexture()->GetHeight());
	pImageUI->SetPos(Vec2D(-80.f, 0.f));
	m_MarkMiniMap = pImageUI;

	pImageUI = new CImageUI;
	pImageUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"MiniMap_BG", L"texture\\HUD\\MiniMap_BG.png"));
	pImageUI->SetScale(pImageUI->GetTexture()->GetWidth(), pImageUI->GetTexture()->GetHeight());
	pImageUI->SetPos(Vec2D(5.f, 10.f));
	pImageUI->AddChildUI(m_MarkMiniMap);

	pPanelUI = new CPanelUI;
	pPanelUI->SetScale(Vec2D(200.f, 50.f));
	pPanelUI->SetPos(Vec2D(250.f, 150.f));
	pPanelUI->SetTexture(CResourceMgr::GetInst()->CreateTextureWithAlpha(L"MiniMap_Panel", 200, 50, Color(160, 0, 0, 0)));
	pPanelUI->AddChildUI(pImageUI);

	AddObject(LAYER_TYPE::UI, pPanelUI);
	

	// Coin Score
	pImageUI = new CImageUI;
	pImageUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"ScoreCoin", L"texture\\HUD\\ScoreCoin.png"));
	pImageUI->SetScale(pImageUI->GetTexture()->GetWidth(), pImageUI->GetTexture()->GetHeight());
	pImageUI->SetPos(0.f, 0.f);

	pScoreUI = new CScoreUI;
	pScoreUI->SetSmallScore(0);
	pScoreUI->SetScale(pScoreUI->GetTexture()->GetWidth(), pScoreUI->GetTexture()->GetHeight());
	pScoreUI->SetPos(30.f, 0.f);

	pPanelUI = new CPanelUI;
	pPanelUI->SetScale(Vec2D(200.f, 0.f));
	pPanelUI->SetPos(m_Resolution.x / 2.f - 30.f, 30.f);
	pPanelUI->AddChildUI(pImageUI);
	pPanelUI->AddChildUI(pScoreUI);
	m_CoinScoreUI = pPanelUI;

	AddObject(LAYER_TYPE::UI, pPanelUI);


	// HighScore
	pImageUI = new CImageUI;
	pImageUI->SetTexture(CResourceMgr::GetInst()->LoadTexture(L"HighScore_Banner", L"texture\\HUD\\HighScore_Banner.png"));
	pImageUI->SetScale(pImageUI->GetTexture()->GetWidth(), pImageUI->GetTexture()->GetHeight());
	pImageUI->SetPos(250.f, -10.f);

	pPanelUI = new CPanelUI;
	pPanelUI->SetScale(Vec2D(700.f, 50.f));
	pPanelUI->SetPos(m_Resolution.x - 20.f - (pPanelUI->GetScale().x / 2.f), 130.f);
	pPanelUI->AddChildUI(pImageUI);
	m_HighScoreUI = pPanelUI;


	// HighScore ScoreUI Setting
	m_vecScore.clear();

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
		pScoreUI = new CScoreUI;
		pScoreUI->SetSmallScore(m_vecScore[digit - 1 - i]);
		float StartPosX = (11 - digit) * (pScoreUI->GetTexture()->GetWidth());
		pScoreUI->SetPos(StartPosX + (pScoreUI->GetTexture()->GetWidth() * i), 30.f);
		pScoreUI->SetScale(pScoreUI->GetTexture()->GetWidth(), pScoreUI->GetTexture()->GetHeight());
		pPanelUI->AddChildUI(pScoreUI);
	}

	AddObject(LAYER_TYPE::UI, pPanelUI);



	// CurScore ScoreUI Setting

	pScoreUI = new CScoreUI;
	pScoreUI->SetBigScore(0);
	pScoreUI->SetScale(pScoreUI->GetTexture()->GetWidth(), pScoreUI->GetTexture()->GetHeight());
	pScoreUI->SetPos(pScoreUI->GetTexture()->GetWidth() * 7, 0.f);

	pPanelUI = new CPanelUI;
	pPanelUI->SetScale(Vec2D(700.f, 50.f));
	pPanelUI->SetPos(m_Resolution.x - 20.f - (pPanelUI->GetScale().x / 2.f), 250.f);
	pPanelUI->AddChildUI(pScoreUI);
	m_CurScoreUI = pPanelUI;

	AddObject(LAYER_TYPE::UI, pPanelUI);


	// Set GameOver PanelUI
	m_GameOverUI = new CPanelUI;
	m_GameOverUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"BlackBackgroundTex"));
	m_GameOverUI->SetScale(m_GameOverUI->GetTexture()->GetWidth(), m_GameOverUI->GetTexture()->GetHeight());
	m_GameOverUI->SetPos(m_Resolution.x / 2.f, m_Resolution.y / 2.f);
	
	pPanelUI = new CPanelUI;
	pPanelUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"GameOver_Panel0"));
	pPanelUI->SetScale(pPanelUI->GetTexture()->GetWidth(), pPanelUI->GetTexture()->GetHeight());
	pPanelUI->SetPos(0, 0);
	m_GameOverUI->AddChildUI(pPanelUI);

	pPanelUI = new CPanelUI;
	pPanelUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"GameOver_Panel1"));
	pPanelUI->SetScale(pPanelUI->GetTexture()->GetWidth(), pPanelUI->GetTexture()->GetHeight());
	pPanelUI->SetPos(0, 0);
	m_GameOverUI->AddChildUI(pPanelUI);

	pImageUI = new CImageUI;
	pImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"Title_Reslut"));
	pImageUI->SetScale(pImageUI->GetTexture()->GetWidth(), pImageUI->GetTexture()->GetHeight());
	pImageUI->SetPos(0, -230);
	m_GameOverUI->AddChildUI(pImageUI);

	pImageUI = new CImageUI;
	pImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"GameOverUI_Deco0"));
	pImageUI->SetScale(pImageUI->GetTexture()->GetWidth(), pImageUI->GetTexture()->GetHeight());
	pImageUI->SetPos(-300, 150);
	m_GameOverUI->AddChildUI(pImageUI);

	pImageUI = new CImageUI;
	pImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"GameOverUI_Deco1"));
	pImageUI->SetScale(pImageUI->GetTexture()->GetWidth(), pImageUI->GetTexture()->GetHeight());
	pImageUI->SetPos(320, 130);
	m_GameOverUI->AddChildUI(pImageUI);

	pImageUI = new CImageUI;
	pImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"GameOverUI_Score"));
	pImageUI->SetScale(pImageUI->GetTexture()->GetWidth(), pImageUI->GetTexture()->GetHeight());
	pImageUI->SetPos(-200, -120);
	m_GameOverUI->AddChildUI(pImageUI);

	pImageUI = new CImageUI;
	pImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"GameOverUI_Coin"));
	pImageUI->SetScale(pImageUI->GetTexture()->GetWidth(), pImageUI->GetTexture()->GetHeight());
	pImageUI->SetPos(-200, -20);
	m_GameOverUI->AddChildUI(pImageUI);

	pButtonUI = new CButtonUI;
	pButtonUI->SetNormalImage(CResourceMgr::GetInst()->FindTexture(L"GameOverUI_NormalBtn"));
	pButtonUI->SetHoverImage(CResourceMgr::GetInst()->FindTexture(L"GameOverUI_HoverBtn"));
	pButtonUI->SetCallBack(&GameOverBtnCallBackFunc);
	pButtonUI->SetScale(194.f, 65.f);
	pButtonUI->SetPos(0, 130);
	m_GameOverUI->AddChildUI(pButtonUI);
}

void CLevel_Game::ShowGameOverUI()
{
	CPanelUI* HighScorePanel = nullptr;
	HighScorePanel = new CPanelUI;
	HighScorePanel->SetScale(500.f, 0.f);
	HighScorePanel->SetPos(-100.f, -200.f);

	m_vecScore.clear();

	// Score UI Setting
	CScoreUI* ScoreUI = nullptr;
	int score = CGameDataMgr::GetInst()->GetCurScore();
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
	m_GameOverUI->AddChildUI(HighScorePanel);

	// Coin UI Setting
	CPanelUI* CoinScorePanel = nullptr;
	CoinScorePanel = new CPanelUI;
	CoinScorePanel->SetScale(500.f, 0.f);
	CoinScorePanel->SetPos(-100.f, -100.f);

	m_vecScore.clear();

	int coin = CGameDataMgr::GetInst()->GetCurGameCoin();
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
		float StartPosX = (11 - coin_digit) * (ScoreUI->GetTexture()->GetWidth());
		ScoreUI->SetPos(StartPosX + (ScoreUI->GetTexture()->GetWidth() * i), 80.f);
		ScoreUI->SetScale(ScoreUI->GetTexture()->GetWidth(), ScoreUI->GetTexture()->GetHeight());
		CoinScorePanel->AddChildUI(ScoreUI);
	}
	m_GameOverUI->AddChildUI(CoinScorePanel);

	AddObject(LAYER_TYPE::UI, m_GameOverUI);

	if (CGameDataMgr::GetInst()->GetHighScore() < CGameDataMgr::GetInst()->GetCurScore())
	{
		CImageUI* ImageUI = new CImageUI;
		ImageUI->SetTexture(CResourceMgr::GetInst()->FindTexture(L"GameOverUI_NewRecord"));
		ImageUI->SetScale(ImageUI->GetTexture()->GetWidth(), ImageUI->GetTexture()->GetHeight());
		ImageUI->SetPos(280, -200);
		m_GameOverUI->AddChildUI(ImageUI);

		CSound* sound = CResourceMgr::GetInst()->FindSound(L"Result_NewRecord");
		sound->SetVolume(80.f);
		sound->Play();
	}
	else
	{
		CSound* sound = CResourceMgr::GetInst()->FindSound(L"Result_ScreenChange");
		sound->SetVolume(80.f);
		sound->Play();
	}
	
}

void CLevel_Game::LoadSoundResource()
{
	// BGM
	CResourceMgr::GetInst()->LoadSound(L"Bgm_MainGame", L"sound\\Bgm_MainGame.wav");
	CResourceMgr::GetInst()->LoadSound(L"Bgm_BonusTime", L"sound\\Bgm_BonusTime.wav");

	// Scene Change Effect
	CResourceMgr::GetInst()->LoadSound(L"Effect_BonusTime_Start", L"sound\\Effect_BonusTime_Start.wav");
	CResourceMgr::GetInst()->LoadSound(L"Result_ScreenChange", L"sound\\Result_ScreenChange.wav");
	CResourceMgr::GetInst()->LoadSound(L"Result_NewRecord", L"sound\\Result_NewRecord.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_GameStart", L"sound\\Effect_GameStart.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_GameEnd", L"sound\\Effect_GameEnd.wav");

	// Char motion Effect
	CResourceMgr::GetInst()->LoadSound(L"Effect_CharJump", L"sound\\Effect_CharJump.wav");        
	CResourceMgr::GetInst()->LoadSound(L"Effect_CharSlide", L"sound\\Effect_CharSlide.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_CharDamage", L"sound\\Effect_CharDamage.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_BigToSmall", L"sound\\Effect_BigToSmall.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_SmallToBig", L"sound\\Effect_SmallToBig.wav");
	
	// Item Effect
	 CResourceMgr::GetInst()->LoadSound(L"Effect_CrashWithBody", L"sound\\Effect_CrashWithBody.wav");
	// TODO : Body 착지 효과음 필요
	
	// Jelly Effect
	CResourceMgr::GetInst()->LoadSound(L"Effect_GetAlphabetJelly", L"sound\\Effect_GetAlphabetJelly.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_GetBigBearJelly", L"sound\\Effect_GetBigBearJelly.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_GetBigCoinJelly", L"sound\\Effect_GetBigCoinJelly.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_GetCoinJelly", L"sound\\Effect_GetCoinJelly.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_GetItemJelly", L"sound\\Effect_GetItemJelly.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_GetNormalJelly", L"sound\\Effect_GetNormalJelly.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_LargeEnergy", L"sound\\Effect_LargeEnergy.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_SmallEnergy", L"sound\\Effect_SmallEnergy.wav");

	// Obstacle Effect
	CResourceMgr::GetInst()->LoadSound(L"Effect_ObstacleDown", L"sound\\Effect_ObstacleDown.wav");
	CResourceMgr::GetInst()->LoadSound(L"Effect_PopUpObstacle", L"sound\\Effect_PopUpObstacle.wav");
}

void CLevel_Game::LoadTextureResource()
{
	CResourceMgr::GetInst()->LoadTexture(L"Best", L"texture\\HUD\\Best2.png");

	CResourceMgr::GetInst()->LoadTexture(L"Jump", L"texture\\HUD\\Jump.png");
	CResourceMgr::GetInst()->LoadTexture(L"Jump_Dim", L"texture\\HUD\\Jump_Dim.png");

	CResourceMgr::GetInst()->LoadTexture(L"Slide", L"texture\\HUD\\Slide.png");
	CResourceMgr::GetInst()->LoadTexture(L"Slide_Dim", L"texture\\HUD\\Slide_Dim.png");

	CResourceMgr::GetInst()->LoadTexture(L"HeartGauge", L"texture\\HUD\\HeartGauge.png");
	CResourceMgr::GetInst()->LoadTexture(L"HeartLife", L"texture\\HUD\\HeartLife.png");

	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_0", L"texture\\HUD\\BonusTime_B.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_1", L"texture\\HUD\\BonusTime_O.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_2", L"texture\\HUD\\BonusTime_N.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_3", L"texture\\HUD\\BonusTime_U.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_4", L"texture\\HUD\\BonusTime_S.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_5", L"texture\\HUD\\BonusTime_T.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_6", L"texture\\HUD\\BonusTime_I.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_7", L"texture\\HUD\\BonusTime_M.png");
	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_8", L"texture\\HUD\\BonusTime_E.png");

	CResourceMgr::GetInst()->LoadTexture(L"BonusTime_BG", L"texture\\HUD\\BonusTime_BG.png");

	CResourceMgr::GetInst()->LoadTexture(L"GameOver_Panel0", L"texture\\HUD\\GameOver_Panel0.png");
	CResourceMgr::GetInst()->LoadTexture(L"GameOver_Panel1", L"texture\\HUD\\GameOver_Panel1.png");
	CResourceMgr::GetInst()->LoadTexture(L"Title_Reslut", L"texture\\HUD\\TiTle_Result.png");
	CResourceMgr::GetInst()->LoadTexture(L"GameOverUI_Deco0", L"texture\\HUD\\GameOverUI_Deco0.png");
	CResourceMgr::GetInst()->LoadTexture(L"GameOverUI_Deco1", L"texture\\HUD\\GameOverUI_Deco1.png");

	CResourceMgr::GetInst()->LoadTexture(L"GameOverUI_Score", L"texture\\HUD\\GameOverUI_Score.png");
	CResourceMgr::GetInst()->LoadTexture(L"GameOverUI_Coin", L"texture\\HUD\\GameOverUI_Coin.png");
	CResourceMgr::GetInst()->LoadTexture(L"GameOverUI_NormalBtn", L"texture\\HUD\\GameOverUI_NormalBtn.png");
	CResourceMgr::GetInst()->LoadTexture(L"GameOverUI_HoverBtn", L"texture\\HUD\\GameOverUI_HoverBtn.png");
	CResourceMgr::GetInst()->LoadTexture(L"GameOverUI_NewRecord", L"texture\\HUD\\GameOverUI_NewRecord.png");
}

void CLevel_Game::SpawnStageSTObject(StageSTObjInfo& _ObjInfo)
{
	Task task = {};
	CObject* pObject = nullptr;

	LAYER_TYPE type = _ObjInfo._objType;
	UINT index = _ObjInfo._typeIndex;
	if (type == LAYER_TYPE::BACKGROUND)	pObject = (m_PostStage->GetBG(static_cast<BG_TYPE>(index)))->Clone();
	else if (type == LAYER_TYPE::PLATFORM) pObject = (m_PostStage->GetPLT(static_cast<PLT_TYPE>(index)))->Clone();
	else if (type == LAYER_TYPE::OBSTACLE) pObject = (m_PostStage->GetOBS(static_cast<OBS_TYPE>(index)))->Clone();

	if ((type == LAYER_TYPE::OBSTACLE) && (index == 3 || index == 6))
	{
		pObject->SetPos(Vec2D(_ObjInfo._pos.x + m_PostStageStartPosX, 0.0f));
	}
	else
	{
		pObject->SetPos(_ObjInfo._pos.x + m_PostStageStartPosX, _ObjInfo._pos.y);
	}

	task.Type = TASK_TYPE::SPAWN_OBJECT;
	task.Param1 = (DWORD_PTR)type;
	task.Param2 = (DWORD_PTR)pObject;

	CTaskMgr::GetInst()->AddTask(task);
}

void CLevel_Game::SpawnStageDNObject(StageDNObjInfo& _ObjInfo)
{
	Task task = {};
	CJelly* pJelly = nullptr;

	pJelly = CJellyMgr::GetInst()->GetVecJelly((UINT)_ObjInfo._objType)[_ObjInfo._typeIndex]->Clone();
	pJelly->SetPos(_ObjInfo._pos.x + m_PostStageStartPosX, _ObjInfo._pos.y);

	task.Type = TASK_TYPE::SPAWN_OBJECT;
	task.Param1 = (DWORD_PTR)LAYER_TYPE::JELLY;
	task.Param2 = (DWORD_PTR)pJelly;

	CTaskMgr::GetInst()->AddTask(task);
}

void CLevel_Game::PrintCookieLog()
{
	DbgObjInfo info = { m_Cookie->GetPos(), m_Cookie->GetScale(),
						L"posX : " + std::to_wstring(m_LogPos.x) +
						L" posY : " + std::to_wstring(m_LogPos.y) };

	CDbgRenderMgr::GetInst()->AddDbgObjInfo(info);
}


