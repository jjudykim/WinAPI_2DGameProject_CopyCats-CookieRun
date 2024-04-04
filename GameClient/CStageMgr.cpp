#include "pch.h"
#include "CStageMgr.h"
#include "CStage.h"

#include "CPathMgr.h"
#include "CResourceMgr.h"

#include "CBackground.h"
#include "CPlatform.h"
#include "CObstacle.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"

CStageMgr::CStageMgr()
	: m_CurrentStageType(STAGE_TYPE::END)
	, m_pCurrentStage(nullptr)
{
}

CStageMgr::~CStageMgr()
{
	for (size_t i = 0; i < (UINT)EPISODE_TYPE::END; ++i)
	{
		Safe_Del_Vec(m_arrStage[i]);
	}
}

void CStageMgr::init()
{
	for (UINT i = 0; i < (UINT)EPISODE_TYPE::END; ++i)
	{
		for (UINT j = 0; j < (UINT)STAGE_TYPE::END; ++j)
		{
			CStage* stg = new CStage;
			stg->SetEPType(static_cast<EPISODE_TYPE>(i));
			stg->SetSTGType(static_cast<STAGE_TYPE>(j));
			m_arrStage[i].push_back(stg);
		}
	}
}

void CStageMgr::progress()
{
}

void CStageMgr::ChangeNextStage()
{
	if (m_pCurrentStage)
	{
		m_pCurrentStage->Exit();
	}

	if ((UINT)m_pCurrentStage->GetSTGType() + 1 != (UINT)STAGE_TYPE::END)
	{
		m_pCurrentStage = m_arrStage[(UINT)m_pCurrentStage->GetEPType()].at((UINT)m_pCurrentStage->GetSTGType() + 1);
		assert(m_pCurrentStage);

		m_pCurrentStage->Enter();
	}
	
}

void CStageMgr::LoadStageInfo(EPISODE_TYPE _EPType)
{
	FILE* pFile = nullptr;
	wstring EP = L"EP" + std::to_wstring((UINT)_EPType + 1);
	wstring Path = CPathMgr::GetInst()->GetContentPath() 
					+ L"stage\\" + EP + L".stg";
	
	_wfopen_s(&pFile, Path.c_str(), L"r");
	if (pFile == nullptr) { return; }
	
	CStage* curStg = new CStage();
	CTexture* tex = nullptr;
	wchar_t szReadBuff[256] = {};
	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		if (wstring(szReadBuff) == L"[BACKGROUND_ATLAS]")
		{
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			tex = CResourceMgr::GetInst()->LoadTexture(EP, szReadBuff);
			
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
		}

		if (wstring(szReadBuff) == L"[STAGE_COUNT]")
		{
			int count = 0;
			fwscanf_s(pFile, L"%d", &count);

			for (int i = 0; i < count; ++i)
			{
				wstring STG = L"STG" + std::to_wstring(count);
				while (true)
				{
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
					if (wstring(szReadBuff) == L"[STAGE_LENGTH]") break;
				}
				fwscanf_s(pFile, L"%f", &curStg->m_StageLength);
				
				while (true)
				{
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
					if (wstring(szReadBuff) == L"==BACKGROUND==") break;
				}
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				Vec2D Pos = {};
				Vec2D Slice = {};
				CBackground* BG;

				for (UINT i = 0; i < (UINT)BG_TYPE::END; ++i)
				{
					fwscanf_s(pFile, L"%f%f%f%f", &Pos.x, &Pos.y, &Slice.x, &Slice.y);
					if (Slice == 0) break;
					curStg->m_arrBG[i] = new CBackground;
					if (i == 1) { curStg->m_arrBG[i]->SetSpeed(10); }
					else if (i == 2) { curStg->m_arrBG[i]->SetSpeed(5); }
					else if (i == 3) { curStg->m_arrBG[i]->SetSpeed(15); }

					BG = curStg->m_arrBG[i];
					BG->SetBGType(static_cast<BG_TYPE>(i));
					BG->SetAtlas(tex);
					BG->SetScale(Slice * 2.25f);
					BG->SetAtlasInfo(Pos, Slice);
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
				}
				tex = nullptr;

				while (true)
				{
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
					if (wstring(szReadBuff) == L"==PLATFORM==") break;
				}
				CPlatform* PLT;

				for (UINT i = 0; i < (UINT)PLT_TYPE::END; ++i)
				{
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
					curStg->m_arrPLT[i] = new CPlatform;
					PLT = curStg->m_arrPLT[i];
					PLT->SetPLTType(static_cast<PLT_TYPE>(i));

					tex = CResourceMgr::GetInst()->LoadTexture(EP + L"_" + STG + L"_PLT" + std::to_wstring(i), szReadBuff);
					PLT->SetTexture(tex);
					Vec2D scale = {};
					fwscanf_s(pFile, L"%f%f", &scale.x, &scale.y);
					PLT->SetScale(scale);

					CCollider* col = PLT->GetComponent<CCollider>();
					if (i == 0) col->SetOffsetPos(Vec2D(0.f, PLT->GetScale().y / 2.f));             // PLT_TYPE::GROUNDED
					else if (i == 1) col->SetOffsetPos(Vec2D(0.f, 0.f));                            // PLT_TYPE::FLOATED
				}
				tex = nullptr;

				while (true)
				{
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
					if (wstring(szReadBuff) == L"==OBSTACLE==") break;
				}
				CObstacle* OBS;
				CAnimator* pAnimator;

				for (UINT i = 0; i < (UINT)OBS_TYPE::END; ++i)
				{
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
					curStg->m_arrOBS[i] = new CObstacle;
					OBS = curStg->m_arrOBS[i];
					OBS->SetOBSType(static_cast<OBS_TYPE>(i));

					tex = CResourceMgr::GetInst()->LoadTexture(EP + L"_" + STG + L"_OBS" + std::to_wstring(i), szReadBuff);
					OBS->SetTexture(tex);

					Vec2D scale = {};
					fwscanf_s(pFile, L"%f%f", &scale.x, &scale.y);
					OBS->SetScale(scale);
		
					CCollider* col = OBS->GetComponent<CCollider>();
					if (i == 8 || i == 9) col->SetOffsetPos(Vec2D(0.f, OBS->GetScale().y / 2.f));     // OBS_TYPE::SLIDE_A, OBS_TYPE::SLIDE_B
					else { col->SetOffsetPos(Vec2D(0.f, (-1.f) * OBS->GetScale().y / 2.f)); }         // else OBS_TYPE

					if (i == 2) // JUMP_UP
					{
						fwscanf_s(pFile, L"%s", szReadBuff, 256);
						pAnimator = (CAnimator*)OBS->AddComponent(new CAnimator);
						pAnimator->LoadAnimation(EP + L"_" + STG + L"_OBS" + std::to_wstring(i), szReadBuff);
					}
					else if (i == 7) // DBJUMP_UP
					{
						fwscanf_s(pFile, L"%s", szReadBuff, 256);
						pAnimator = (CAnimator*)OBS->AddComponent(new CAnimator);
						pAnimator->LoadAnimation(EP + L"_" + STG + L"_OBS" + std::to_wstring(i), szReadBuff);
					}
					
				}
				tex = nullptr;

				m_arrStage[(UINT)_EPType].at(i) = curStg;
			}
		}
	}

	

	fclose(pFile);
}
