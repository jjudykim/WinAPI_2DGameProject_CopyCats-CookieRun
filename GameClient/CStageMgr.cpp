#include "pch.h"
#include "CStageMgr.h"
#include "CStage.h"

#include "CPathMgr.h"
#include "CResourceMgr.h"

#include "CBackground.h"
#include "CPlatform.h"
#include "CObstacle.h"
#include "CTile.h"

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
	
	CStage* curStg = nullptr;
	CTexture* BGtex = nullptr;
	CTexture* tex = nullptr;
	wchar_t szReadBuff[256] = {};
	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		if (wstring(szReadBuff) == L"[BACKGROUND_ATLAS]")
		{
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			BGtex = CResourceMgr::GetInst()->LoadTexture(EP, szReadBuff);
			
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
		}

		if (wstring(szReadBuff) == L"[STAGE_COUNT]")
		{
			int count = 0;
			fwscanf_s(pFile, L"%d", &count);

			for (int i = 0; i < count; ++i)
			{
				curStg = new CStage();
				wstring STG = L"STG" + std::to_wstring(i + 1);
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
					if (Slice == 0)
					{
						curStg->m_arrBG[i] = nullptr;
						break;
					}
					curStg->m_arrBG[i] = new CBackground;
					if (i == 1) { curStg->m_arrBG[i]->SetSpeed(10); }
					else if (i == 2) { curStg->m_arrBG[i]->SetSpeed(5); }
					else if (i == 3) { curStg->m_arrBG[i]->SetSpeed(15); }

					BG = curStg->m_arrBG[i];
					BG->SetBGType(static_cast<BG_TYPE>(i));
					BG->SetAtlas(BGtex);
					BG->SetScale(Slice * 2.25f);
					BG->SetAtlasInfo(Pos, Slice);
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
				}

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
					PLT->SetScale(tex->GetWidth(), tex->GetHeight());

					CCollider* col = PLT->GetComponent<CCollider>();
					col->SetOffsetPos(Vec2D(0.f, PLT->GetScale().y / 2.f));
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
					OBS->SetScale(tex->GetWidth(), tex->GetHeight());
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
						pAnimator->LoadAnimation(EP + L"_" + STG + L"_OBS_jumpNoti", szReadBuff);
						fwscanf_s(pFile, L"%s", szReadBuff, 256);
						pAnimator->LoadAnimation(EP + L"_" + STG + L"_OBS" + std::to_wstring(i), szReadBuff);
						pAnimator->Play(EP + L"_" + STG + L"_OBS_jumpNoti", true);
					}
					else if (i == 7) // DBJUMP_UP
					{
						fwscanf_s(pFile, L"%s", szReadBuff, 256);
						pAnimator = (CAnimator*)OBS->AddComponent(new CAnimator);
						pAnimator->LoadAnimation(EP + L"_" + STG + L"_OBS_jumpNoti", szReadBuff);
						fwscanf_s(pFile, L"%s", szReadBuff, 256);
						pAnimator->LoadAnimation(EP + L"_" + STG + L"_OBS" + std::to_wstring(i), szReadBuff);
						pAnimator->Play(EP + L"_" + STG + L"_OBS_jumpNoti", true);
					}
				}
				tex = nullptr;

				m_arrStage[(UINT)_EPType].at(i) = curStg;
				m_arrStage[(UINT)_EPType].at(i)->SetEPType(_EPType);
				m_arrStage[(UINT)_EPType].at(i)->SetSTGType(static_cast<STAGE_TYPE>(i));
			}
		}
	}

	fclose(pFile);
}

void CStageMgr::SaveStageSTObject(CStage* _SaveStage)
{
	// ex) EP1_STG1_STObj.stg
	wstring FileName = L"EP" + std::to_wstring((UINT)_SaveStage->GetEPType() + 1)
		+ L"_STG" + std::to_wstring((UINT)_SaveStage->GetSTGType() + 1)
		+ L"_STObj.stg";

	wstring FilePath = CPathMgr::GetInst()->GetContentPath() + L"stage\\" + FileName;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, FilePath.c_str(), L"w");

	if (nullptr == pFile)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"스테이지 스태틱 오브젝트 저장 실패");
		return;
	}

	for (UINT i = 0; i < 3; ++i)
	{
		fwprintf_s(pFile, L"[OBJECT_TYPE]\n");

		wstring strObjType = L"";
		if (i == 0) strObjType = L"BACKGROUND";
		else if (i == 1) strObjType = L"PLATFORM";
		else if (i == 2) strObjType = L"OBSTACLE";
		fwprintf_s(pFile, L"%s\n\n", strObjType.c_str());

		fwprintf_s(pFile, L"[OBJECT_COUNT]\n");

		const vector<StageSTObjInfo>& _Info = _SaveStage->GetSTObjInfo(i);
		int size = _Info.size();
		fwprintf_s(pFile, L"%d\n\n", size);

		for (int j = 0; j < size; ++j)
		{
			fwprintf_s(pFile, L"[TYPE_INDEX] ");
			fwprintf_s(pFile, L"%d\n", _Info[j]._typeIndex);

			fwprintf_s(pFile, L"[STARTPOS] ");
			fwprintf_s(pFile, L"%f %f\n\n", _Info[j]._pos.x, _Info[j]._pos.y);
		}

		_SaveStage->ClearSTObjInfo(i);
	}

	fclose(pFile);
}

void CStageMgr::SaveStageDNObject(CStage* _SaveStage)
{
	wstring FileName = L"EP" + std::to_wstring((UINT)_SaveStage->GetEPType() + 1)    
		+ L"_STG" + std::to_wstring((UINT)_SaveStage->GetSTGType() + 1)
		+ L"_DNObj.stg";

	wstring FilePath = CPathMgr::GetInst()->GetContentPath() + L"stage\\" + FileName;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, FilePath.c_str(), L"w");

	if (nullptr == pFile)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"스테이지 다이나믹 오브젝트 저장 실패");
		return;
	}

	for (UINT i = 0; i < _SaveStage->GetTile()->GetCol(); ++i)
	{
		fwprintf_s(pFile, L"[COL] ");
		for (UINT j = 0; j < _SaveStage->GetTile()->GetRow(); ++j)
		{
			char Row = _SaveStage->GetTile()->GetJellyDataByCol(i)[j];
			fwprintf_s(pFile, L"%d ", (int)Row);
		}
		fwprintf_s(pFile, L"[END]\n");
	}

	_SaveStage->ClearDNObjInfo();

	fclose(pFile);
}
