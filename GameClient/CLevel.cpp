#include "pch.h"
#include "CLevel.h"

#include "CObject.h"
#include "CCollider.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	for (size_t i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		Safe_Del_Vec(m_arrObj[i]);
	}
}

void CLevel::AddObject(LAYER_TYPE _Layer, CObject* _Object)
{
	m_arrObj[(UINT)_Layer].push_back(_Object);
	_Object->m_Type = _Layer;
}

void CLevel::begin()
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->begin();
		}
	}
}

void CLevel::tick()
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->tick();
		}
	}
}

void CLevel::finaltick()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		m_arrCollider[i].clear();
	}

	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finaltick();
		}
	}
}

void CLevel::render()
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->render();
		}
	}
}

void CLevel::RegisterCollider(CCollider* _Collider)
{
	LAYER_TYPE Layer = _Collider->GetOwner()->GetLayerType();
	m_arrCollider[(UINT)Layer].push_back(_Collider);
}


