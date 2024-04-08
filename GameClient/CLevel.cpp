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
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			if ((*iter)->IsDead())
			{
				iter = m_arrObj[i].erase(iter);
			}
			else
			{
				(*iter)->tick();
				++iter;
			}
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
			/*float MinPosX = CCamera::GetInst()->GetLookAt().x - (CEngine::GetInst()->GetResolution().x / 2.f);
			float MaxPosX = CCamera::GetInst()->GetLookAt().x + (CEngine::GetInst()->GetResolution().x / 2.f);
			if (MinPosX <= m_arrObj[i][j]->GetPos().x + m_arrObj[i][j]->GetScale().x
				&& m_arrObj[i][j]->GetPos().x <= MaxPosX)
			{
				
			}*/

			m_arrObj[i][j]->render();
		}
	}
}

void CLevel::RegisterCollider(CCollider* _Collider)
{
	LAYER_TYPE Layer = _Collider->GetOwner()->GetLayerType();
	m_arrCollider[(UINT)Layer].push_back(_Collider);
}

CObject* CLevel::FindObjectByName(const wstring& _Name)
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		CObject* pFindObj = FindObjectByName((LAYER_TYPE)i, _Name);

		if (pFindObj)
		{
			return pFindObj;
		}
	}

	return nullptr;
}

CObject* CLevel::FindObjectByName(LAYER_TYPE _Type, const wstring& _Name)
{
	for (size_t i = 0; i < m_arrObj[(UINT)_Type].size(); ++i)
	{
		if (_Name == m_arrObj[(UINT)_Type][i]->GetName())
		{
			return m_arrObj[(UINT)_Type][i];
		}
	}

	return nullptr;
}

void CLevel::SortObjectsByXpos(LAYER_TYPE _Layer)
{
	std::sort(m_arrObj[(UINT)_Layer].begin(), m_arrObj[(UINT)_Layer].begin(), [](const CObject* a, const CObject* b)
		{
			return a->GetPos().x < b->GetPos().x;
		});
}

