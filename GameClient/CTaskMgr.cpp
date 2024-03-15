#include "pch.h"
#include "CTaskMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObject.h"

CTaskMgr::CTaskMgr()
{}

CTaskMgr::~CTaskMgr()
{}

void CTaskMgr::tick()
{
	ClearGC();
	ExectueTask();
}

void CTaskMgr::ClearGC()
{
	Safe_Del_Vec(m_GC);
	m_GC.clear();
}

void CTaskMgr::ExectueTask()
{
	static bool bLevelChanged = false;
	bLevelChanged = false;

	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		switch (m_vecTask[i].Type)
		{
		case TASK_TYPE::SPAWN_OBJECT:
		{
			LAYER_TYPE Layer = (LAYER_TYPE)m_vecTask[i].Param1;
			CObject* pObj = (CObject*)m_vecTask[i].Param2;

			GET_CUR_LEVEL->AddObject(Layer, pObj);
			pObj->begin();
		}
			break;

		case TASK_TYPE::DELETE_OBJECT:
		{
			CObject* pObj = (CObject*)m_vecTask[i].Param1;
			if (pObj->m_bDead)
			{
				continue;
			}
			pObj->m_bDead = true;
			m_GC.push_back(pObj);
		}
			break;

		case TASK_TYPE::CHANGE_LEVEL:
		{
			assert(!bLevelChanged);
			bLevelChanged = true;

			LEVEL_TYPE NextType = (LEVEL_TYPE)m_vecTask[i].Param1;
			CLevelMgr::GetInst()->ChangeLevel(NextType);
		}
			break;
		}
	}

	m_vecTask.clear();
}
