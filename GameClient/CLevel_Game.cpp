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
#include "CPlatform.h"
#include "CObstacle.h"
#include "CStage.h"
#include "CJelly.h"
#include "CSound.h"

// TODO : 테스트용. 나중에 지워도 되는 헤더들
#include "CCollider.h"

#include "CAnimator.h"

CLevel_Game::CLevel_Game()
	: m_Cookie(nullptr)
	, m_Pet(nullptr)
	, m_ActingPosX(0)
	, m_DeletePosX(0)
	, m_PostStageStartPosX(0)
	, m_BGM(nullptr)
	, m_CookieStateAction(0)
	, m_PrevStage(nullptr)
	, m_PostStage(nullptr)
	, m_CurStage(nullptr)
	, m_ResolutionWidth(0)
{
	
}

CLevel_Game::~CLevel_Game()
{
}

void CLevel_Game::begin()
{
	CLevel::begin();

	m_ActingPosX = 0;
	m_DeletePosX = m_ResolutionWidth;

	// Timer Setting
	CTimeMgr::GetInst()->AddTimer(0.25f, [this]() {
		m_LogPos = m_Cookie->GetPos();
		}, true);

	CTimeMgr::GetInst()->AddTimer(0.1f, [this]() {
		CGameDataMgr::GetInst()->AddScore(10);
		}, true);

	m_BGM = CResourceMgr::GetInst()->FindSound(L"Bgm_MainGame");
	m_BGM->SetVolume(50.f);
	m_BGM->PlayToBGM();
}

void CLevel_Game::tick()
{
	// Editor Level 진입
	if (CKeyMgr::GetInst()->GetKeyState(KEY::E) == KEY_STATE::TAP)
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}

	CLevel::tick();

	if (m_Cookie == nullptr)
		return;

	UINT EP = (UINT)m_CurStage->GetEPType();
	UINT STG = (UINT)m_CurStage->GetSTGType();
	
	CCamera::GetInst()->SetCameraFocus();

	float StandardPosX = m_Cookie->GetPos().x;
	m_ActingPosX = StandardPosX + 800.f;
	m_DeletePosX = StandardPosX - m_ResolutionWidth * 0.5f;


	// Cookie Debug Info
	CCollider* CookieCol = m_Cookie->GetComponent<CCollider>();
	DbgObjInfo CookieColInfo = { CCamera::GetInst()->GetRealPos(Vec2D(600, 50)), 0, L"Cookie Overlap Count : " + std::to_wstring(CookieCol->GetOverlapCount()) };
	CDbgRenderMgr::GetInst()->AddDbgObjInfo(CookieColInfo);

	PrintCookieLog();

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

	// Delete Passed Stage Object
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
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
	if (m_Cookie->CheckCookieState(COOKIE_COMPLEX_STATE::INVINCIBLE))
	{
		DbgObjInfo info = { CCamera::GetInst()->GetRealPos(Vec2D(300, 50)), 0, L"INVINCIBLE ON" };
		CDbgRenderMgr::GetInst()->AddDbgObjInfo(info);

		if (!(m_CookieStateAction & (int)COOKIE_COMPLEX_STATE::INVINCIBLE))
		{
			m_CookieStateAction |= (int)COOKIE_COMPLEX_STATE::INVINCIBLE;

			CTimeMgr::GetInst()->AddTimer(3.f, [this]() {
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
				m_Cookie->SetScale(m_Cookie->GetScale() + (m_Cookie->GetScale() * DT * 4.f));
				CookieCol->SetScale(CookieCol->GetScale() + (CookieCol->GetScale() * DT * 4.f));
			}
			else if (m_Cookie->GetDefaultScale() * 2.f < m_Cookie->GetScale())
			{
				m_Cookie->SetScale(m_Cookie->GetDefaultScale() * 2.f);
				CookieCol->SetScale(m_Cookie->GetColliderDefaultScale() * 2.f);

				CTimeMgr::GetInst()->AddTimer(3.f, [this, &CookieCol]() {
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
			m_Cookie->SetSpeed(m_Cookie->GetSpeed() * 2.f);

			/*CTimeMgr::GetInst()->AddTimer(3.f, [this]() {
				m_Cookie->TurnOnCookieState(COOKIE_COMPLEX_STATE::INVINCIBLE);
				m_Cookie->TurnOffCookieState(COOKIE_COMPLEX_STATE::BOOST);
				LOG(LOG_TYPE::DBG_LOG, L"INVINCIBLE OFF");
				m_CookieStateAction &= ~(int)COOKIE_COMPLEX_STATE::BOOST;
				}, false);*/
		}
	}
	
	// Stage Change Check
	if (m_PostStageStartPosX < StandardPosX + m_ResolutionWidth)
	{
		m_PrevStage = m_CurStage;
		CStageMgr::GetInst()->ChangeNextStage();
		m_PostStage = CStageMgr::GetInst()->GetCurrentStage();
		m_PostStage->LoadSTObjectsFromFile();
		m_PostStage->LoadDNObjectsFromFile();
		
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

	if (m_PrevStage != nullptr
		&& m_PostStageStartPosX - m_PostStage->GetSTGLength() < CCamera::GetInst()->GetRealPos(Vec2D(0, 0)).x)
	{
		m_PrevStage->Exit();
		m_PrevStage = nullptr;
		m_CurStage = m_PostStage;
		m_PostStage = nullptr;
	}
}


void CLevel_Game::Enter()
{
	m_ResolutionWidth = CEngine::GetInst()->GetResolution().x;
	
	LoadSoundResource();

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
	pPlayer->SetCurCookie(COOKIE_TYPE::BRAVE_COOKIE);
	pPlayer->SetPos(COOKIE_DEFAULT_POSX, COOKIE_DEFAULT_POSY);
	pPlayer->SetScale(pPlayer->GetCurCookie()._frmSize.x, pPlayer->GetCurCookie()._frmSize.y);
	pPlayer->SetSpeed(400.f);

	m_Cookie = pPlayer;
	CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::SPAWN_OBJECT, (DWORD_PTR)LAYER_TYPE::PLAYER, (DWORD_PTR)pObject });

	pObject = new CPet;
	pObject->SetName(L"Pet");
	CPet* pPet = dynamic_cast<CPet*>(pObject);
	pPet->SetCurPet(PET_TYPE::GOLD_DROP);
	pPet->SetPos(PET_DEFAULT_POSX, PET_DEFAULT_POSY);
	pPet->SetScale(pPet->GetCurPet()._frmSize.x, pPet->GetCurPet()._frmSize.y);
	pPet->SetSpeed(400.f);

	m_Pet = pPet;
	CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::SPAWN_OBJECT, (DWORD_PTR)LAYER_TYPE::PET, (DWORD_PTR)pObject });
	
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::OBSTACLE);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::JELLY);

	m_PostStageStartPosX = m_CurStage->GetSTGLength();
}

void CLevel_Game::Exit()
{
	m_BGM->Stop();
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
	pJelly->SetPos(_ObjInfo._pos);

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


