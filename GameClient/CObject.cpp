#include "pch.h"
#include "CObject.h"

#include "CEngine.h"
#include "CJelly.h"
#include "CComponent.h"
#include "CAnimator.h"

CObject::CObject()
	: m_Animator(nullptr)
{
}

CObject::~CObject()
{
	Safe_Del_Vec(m_vecCom);
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
	if (m_Animator == nullptr)
	{
		CJelly* curJelly = dynamic_cast<CJelly*>(this);
		curJelly->render();
		return;
	}
	
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


