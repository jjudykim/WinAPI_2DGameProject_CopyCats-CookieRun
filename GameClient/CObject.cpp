#include "pch.h"
#include "CObject.h"

#include "CEngine.h"

#include "CComponent.h"
#include "CAnimator.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

void CObject::begin()
{
}

void CObject::tick()
{
}

void CObject::finaltick()
{
}

void CObject::render()
{
	Rectangle(DC,(int)(m_Pos.x - m_Scale.x * 0.5f)
				,(int)(m_Pos.y - m_Scale.y * 0.5f)
				,(int)(m_Pos.x + m_Scale.x * 0.5f)
				,(int)(m_Pos.y + m_Scale.y * 0.5f));
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


