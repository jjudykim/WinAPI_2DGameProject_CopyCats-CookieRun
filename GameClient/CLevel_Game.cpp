#include "pch.h"
#include "CLevel_Game.h"

#include "CCollisionMgr.h"
#include "CDbgRenderMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CStageMgr.h"
#include "CTaskMgr.h"

#include "CEngine.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CPet.h"
#include "CBackground.h"
#include "CPlatform.h"
#include "CObstacle.h"
#include "CStage.h"

CLevel_Game::CLevel_Game()
	: m_Cookie(nullptr)
	, m_SpawnPosX(0)
	, m_DeletePosX(0)
{
	
}

CLevel_Game::~CLevel_Game()
{
}

void CLevel_Game::begin()
{
	CLevel::begin();

	m_SpawnPosX = 0;
	m_DeletePosX = m_ResolutionWidth;

}

void CLevel_Game::tick()
{
	CLevel::tick();

	if (m_Cookie == nullptr)
		return;

	// TODO: test
	if (CKeyMgr::GetInst()->GetKeyState(KEY::E) == KEY_STATE::TAP)
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}


	float StandardPosX = m_Cookie->GetPos().x;
	m_SpawnPosX = StandardPosX + m_ResolutionWidth;
	m_DeletePosX = StandardPosX - m_ResolutionWidth * 0.5f;

	vector<StageSTObjInfo>& vecStageInfo = m_CurStage->m_vecStageInfo;
	vector<StageSTObjInfo>::iterator iter = vecStageInfo.begin();
	for (; iter != vecStageInfo.end(); )
	{
		if (iter->_pos.x <= m_SpawnPosX)
		{
			SpawnStageObject(*iter);
			iter = vecStageInfo.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	// Delete Passed Stage Object
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GET_CUR_LEVEL->GetObjects(static_cast<LAYER_TYPE>(i));

		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			float tPosX = 0.0f;
			if (vecObj[j]->GetLayerType() == LAYER_TYPE::BACKGROUND)
			{
				tPosX = vecObj[j]->GetPos().x + vecObj[j]->GetScale().x * 2.25;
			}
			else
			{
				tPosX = vecObj[j]->GetPos().x + vecObj[j]->GetScale().x;
			}

			if (tPosX <= m_DeletePosX)
			{
				vecObj[j]->Destroy();
				LOG(LOG_TYPE::DBG_LOG, L"Stage Obejct Deleted");
			}
		}
	}

	// Cookie Debug Info
	if (m_QuaterSecond >= 0.25f)
	{
		m_LogPos = m_Cookie->GetPos();
		m_LogPetPos = m_Pet->GetPos();
		m_QuaterSecond = 0.f;
	}
	DbgObjInfo info = { m_Cookie->GetPos(), m_Cookie->GetScale(),
						L"posX : " + std::to_wstring(m_LogPos.x) +
						L" posY : " + std::to_wstring(m_LogPos.y) };

	DbgObjInfo info2 = { m_Pet->GetPos(), m_Pet->GetScale(),
						L"posX : " + std::to_wstring(m_LogPetPos.x) +
						L"posY : " + std::to_wstring(m_LogPetPos.y) };

	CDbgRenderMgr::GetInst()->AddDbgObjInfo(info);
	CDbgRenderMgr::GetInst()->AddDbgObjInfo(info2);

	m_QuaterSecond += DT;
}


void CLevel_Game::Enter()
{
	m_ResolutionWidth = CEngine::GetInst()->GetResolution().x;
	
	// 현재 스테이지 맵 데이터 불러오기
	CStageMgr::GetInst()->SetStartStage(EPISODE_TYPE::EP1);
	m_CurStage = CStageMgr::GetInst()->GetCurrentStage();
	m_CurStage->LoadFromFile();

	CObject* pObject = new CPlayer;
	pObject->SetName(L"Player");
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObject);
	pPlayer->SetCurCookie(COOKIE_TYPE::ANGEL_COOKIE);
	pObject->SetPos(COOKIE_DEFAULT_POSX, COOKIE_DEFAULT_POSY);
	pObject->SetScale(pPlayer->GetCurCookie()._frmSize.x, pPlayer->GetCurCookie()._frmSize.y);
	pObject->SetSpeed(400.f);
	
	m_Cookie = pObject;
	AddObject(LAYER_TYPE::PLAYER, pObject);

	pObject = new CPet;
	pObject->SetName(L"Pet");
	CPet* pPet = dynamic_cast<CPet*>(pObject);
	pPet->SetCurPet(PET_TYPE::GOLD_DROP);
	pObject->SetPos(PET_DEFAULT_POSX, PET_DEFAULT_POSY);
	pObject->SetScale(pPet->GetCurPet()._frmSize.x, pPet->GetCurPet()._frmSize.y);
	pObject->SetSpeed(400.f);

	m_Pet = pObject;
	AddObject(LAYER_TYPE::PET, pObject);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::JELLY);

	CCamera::GetInst()->SetCameraFocus();
}

void CLevel_Game::Exit()
{
}

void CLevel_Game::SpawnStageObject(StageSTObjInfo& _ObjInfo)
{
	Task task = {};
	CObject* pObject = nullptr;

	LAYER_TYPE type = _ObjInfo._objType;
	UINT index = _ObjInfo._typeIndex;
	if (type == LAYER_TYPE::BACKGROUND)	pObject = (m_CurStage->GetBG(static_cast<BG_TYPE>(index)))->Clone();
	else if (type == LAYER_TYPE::PLATFORM) pObject = (m_CurStage->GetPLT(static_cast<PLT_TYPE>(index)))->Clone();
	else if (type == LAYER_TYPE::OBSTACLE) pObject = (m_CurStage->GetOBS(static_cast<OBS_TYPE>(index)))->Clone();

	pObject->SetPos(_ObjInfo._pos);
	pObject->SetScale(_ObjInfo._scale);

	task.Type = TASK_TYPE::SPAWN_OBJECT;
	task.Param1 = (DWORD_PTR)type;
	task.Param2 = (DWORD_PTR)pObject;

	CTaskMgr::GetInst()->AddTask(task);
}


