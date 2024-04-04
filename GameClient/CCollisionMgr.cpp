#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevel.h"
#include "CLevelMgr.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_Matrix{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::init()
{
}

void CCollisionMgr::tick()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	for (int Row = 0; Row < (UINT)LAYER_TYPE::END; ++Row)
	{
		for (int Col = Row; Col < (UINT)LAYER_TYPE::END; ++Col)
		{
			if (m_Matrix[Row] & (1 << Col))
			{
				const vector<CCollider*>& vecLeft = pCurLevel->GetColliders((LAYER_TYPE)Row);
				const vector<CCollider*>& vecRight = pCurLevel->GetColliders((LAYER_TYPE)Col);

				for (size_t i = 0; i < vecLeft.size(); ++i)
				{
					for (size_t j = 0; j < vecRight.size(); ++j)
					{
						COLLIDER_ID id = {};

						id.LeftID = vecLeft[i]->GetID();
						id.RightID = vecRight[j]->GetID();

						map<ULONGLONG, bool>::iterator iter = m_mapCollisionInfo.find(id.ID);

						if (iter == m_mapCollisionInfo.end())
						{
							m_mapCollisionInfo.insert(make_pair(id.ID, false));
							iter = m_mapCollisionInfo.find(id.ID);
						}

						if (IsCollision(vecLeft[i], vecRight[j]))
						{
							if (iter->second)
							{
								vecLeft[i]->OnOverlap(vecRight[j]);
								vecRight[j]->OnOverlap(vecLeft[i]);
							}
							else
							{
								vecLeft[i]->BeginOverlap(vecRight[j]);
								vecRight[j]->BeginOverlap(vecLeft[i]);
							}

							iter->second = true;
						}
						else
						{
							if (iter->second)
							{
								vecLeft[i]->EndOverlap(vecRight[j]);
								vecRight[j]->EndOverlap(vecLeft[i]);
							}

							iter->second = false;
						}
					}
				}
			}
		}
	}
}

void CCollisionMgr::CollisionCheck(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2)
{
	UINT Row = (UINT)_Layer1;
	UINT Col = (UINT)_Layer2;

	if (Row > Col)
	{
		Row = (UINT)_Layer2;
		Col = (UINT)_Layer1;
	}

	m_Matrix[Row] |= (1 << Col);
}

void CCollisionMgr::CollisionUnCheck(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2)
{
	UINT Row = (UINT)_Layer1;
	UINT Col = (UINT)_Layer2;

	if (Row > Col)
	{
		Row = (UINT)_Layer2;
		Col = (UINT)_Layer1;
	}

	m_Matrix[Row] &= ~(1 << Col);
}

bool CCollisionMgr::IsCollision(CCollider* _Left, CCollider* _Right)
{
	if (_Left->GetID() == _Right->GetID()) return false;

	Vec2D vLeftPos = _Left->GetFinalPos();
	Vec2D vLeftScale = _Left->GetScale();

	Vec2D vRightPos = _Right->GetFinalPos();
	Vec2D vRightScale = _Right->GetScale();

	if (abs(vLeftPos.x - vRightPos.x) <= (vLeftScale.x + vRightScale.x) * 0.5f
		&& abs(vLeftPos.y - vRightPos.y) <= (vLeftScale.y + vRightScale.y) * 0.5f)
	{
		return true;
	}

	return false;
}