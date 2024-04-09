#include "pch.h"
#include "CObject.h"

#include "CEngine.h"
#include "CTaskMgr.h"
#include "CJelly.h"
#include "CDraw.h"
#include "CComponent.h"
#include "CAnimator.h"
#include "CCamera.h"

CObject::CObject()
	: m_Type(LAYER_TYPE::NONE)
	, m_bDead(false)
	, m_Animator(nullptr)
	, m_Speed(0.f)
{
}

CObject::CObject(const CObject& _Other)
	: CEntity(_Other)
	, m_Pos(_Other.m_Pos)
	, m_Scale(_Other.m_Scale)
	, m_Speed(_Other.m_Speed)
	, m_Animator(nullptr)
	, m_Type(_Other.m_Type)
	, m_bDead(false)
{
	for (size_t i = 0; i < _Other.m_vecCom.size(); ++i)
	{
		AddComponent(_Other.m_vecCom[i]->Clone());
	}
}


CObject::~CObject()
{
	Safe_Del_Vec(m_vecCom);
}

void CObject::Destroy()
{
	Task task = {};
	task.Type = TASK_TYPE::DELETE_OBJECT;
	task.Param1 = (DWORD_PTR)this;

	CTaskMgr::GetInst()->AddTask(task);
}

void CObject::begin()
{
}

void CObject::tick()
{
}

void CObject::finaltick()
{
	for (size_t i = 0; i < m_vecCom.size(); ++i)
	{
		m_vecCom[i]->finaltick();
	}
}

void CObject::render()
{
	if (!(RENDER_MINPOSX <= (GetPos().x + GetScale().x) && GetPos().x - GetScale().x <= RENDER_MAXPOSX)) return;

	if (this == nullptr)
		return;

	/*if (m_Animator == nullptr)
	{
		CJelly* curJelly = dynamic_cast<CJelly*>(this);
		if (curJelly != nullptr)
			curJelly->render();

		CDraw* curDraw = dynamic_cast<CDraw*>(this);
		if (curDraw != nullptr)
			curDraw->render();

		return;
	}*/
	
	m_Animator->render();
}

CComponent* CObject::AddComponent(CComponent* _Component)
{
	m_vecCom.push_back(_Component);
	_Component->m_Owner = this;

	if (m_Animator == nullptr)
	{
		m_Animator = dynamic_cast<CAnimator*>(_Component);
	}

	return _Component;
}



