#include "pch.h"
#include "CLevel_Game.h"

#include "CCollisionMgr.h"
#include "CDbgRenderMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CTaskMgr.h"

#include "CEngine.h"
#include "CObject.h"
#include "CPlayer.h"
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

	vector<StageObjInfo>& vecStageInfo = m_CurStage->m_vecStageInfo;
	vector<StageObjInfo>::iterator iter = vecStageInfo.begin();
	for (; iter != vecStageInfo.end(); )
	{
		if (iter->_startPos.x <= m_SpawnPosX)
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
			float tPosX = vecObj[j]->GetPos().x + vecObj[j]->GetScale().x;
			if (tPosX <= m_DeletePosX)
			{
				vecObj[j]->Destroy();

			}
		}
	}


	// Cookie Debug Info
	if (m_QuaterSecond >= 0.25f)
	{
		m_LogPos = m_Cookie->GetPos();
		m_QuaterSecond = 0.f;
	}
	DbgObjInfo info = { m_Cookie->GetPos(), m_Cookie->GetScale(),
						L"posX : " + std::to_wstring(m_LogPos.x) +
						L" posY : " + std::to_wstring(m_LogPos.y) };
	CDbgRenderMgr::GetInst()->AddDbgObjInfo(info);

	/*DbgRenderInfo cookieDbg = { DBG_SHAPE::RECT,
								CCamera::GetInst()->GetRenderPos(m_Cookie->GetPos()),
								m_Cookie->GetScale(),
								PEN_TYPE::PEN_BLUE,
								0, 0};

	CDbgRenderMgr::GetInst()->AddDbgRenderInfo(cookieDbg);*/
	m_QuaterSecond += DT;
}


void CLevel_Game::Enter()
{
	m_ResolutionWidth = CEngine::GetInst()->GetResolution().x;
	

	// ���� �������� �� ������ �ҷ�����
	m_CurStage = new CStage();
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"stage\\Ep1_1st_stage.stg";
	LoadFromFile(strFilePath);

	// ���� �������� �� ������ �ҷ�����
	//...

	CObject* pObject = new CPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(COOKIE_DEFAULT_POSX, COOKIE_DEFAULT_POSY);
	pObject->SetScale(100.f, 200.f);
	pObject->SetSpeed(400.f);
	m_Cookie = pObject;
	AddObject(LAYER_TYPE::PLAYER, pObject);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::JELLY);

	CCamera::GetInst()->SetCameraFocus();
}

void CLevel_Game::Exit()
{
}

void CLevel_Game::SpawnStageObject(StageObjInfo& _ObjInfo)
{
	Task task = {};
	CObject* pObject = nullptr;

	LAYER_TYPE type = _ObjInfo._objType;
	UINT index = _ObjInfo._typeIndex;
	if (type == LAYER_TYPE::BACKGROUND)	pObject = new CBackground(index);
	else if (type == LAYER_TYPE::PLATFORM) pObject = new CPlatform(index);
	else if (type == LAYER_TYPE::OBSTACLE) pObject = new CObstacle(index);

	pObject->SetPos(_ObjInfo._startPos);
	pObject->SetScale(_ObjInfo._scale);
	pObject->SetSpeed(_ObjInfo._speed);

	pObject->SetImage(CAssetMgr::GetInst()->LoadTexture(_ObjInfo._imageName, _ObjInfo._path));
	pObject->SetAtlasInfo(_ObjInfo._atlas, _ObjInfo._slicePos, _ObjInfo._sliceSize);

	task.Type = TASK_TYPE::SPAWN_OBJECT;
	task.Param1 = (DWORD_PTR)type;
	task.Param2 = (DWORD_PTR)pObject;

	CTaskMgr::GetInst()->AddTask(task);
}

void CLevel_Game::LoadFromFile(const wstring& _FullPath)
{
	m_CurStage->LoadFromFile(_FullPath);
	
}

