#include "pch.h"
#include "CStageMgr.h"
#include "CStage.h"

#include "CPathMgr.h"
#include "CResourceMgr.h"

#include "CBackground.h"
#include "CPlatform.h"
#include "CObstacle.h"

CStageMgr::CStageMgr()
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
	wstring EP = L"ep" + std::to_wstring((UINT)_EPType + 1);
	wstring Path = CPathMgr::GetInst()->GetContentPath() 
					+ L"\\stage\\" + EP + L".stg";
	
	_wfopen_s(&pFile, Path.c_str(), L"r");
	if (pFile == nullptr) { return; }
	
	CStage* curStg = new CStage();
	wchar_t szReadBuff[256] = {};
	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		if (wstring(szReadBuff) == L"[BACKGROUND_ATLAS]")
		{
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			CTexture* tex = CResourceMgr::GetInst()->LoadTexture(L"EP" + std::to_wstring((UINT)_EPType + 1), szReadBuff);
			
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			if (wstring(szReadBuff) == L"[STAGE_COUNT]")
			{
				int count = 0;
				fwscanf_s(pFile, L"%d", &count);

				for (int i = 0; i < count; ++i)
				{
					wstring STG = L"stg" + std::to_wstring(count);

					do { fwscanf_s(pFile, L"%s", szReadBuff, 256); } while (wstring(szReadBuff) == L"==BACKGROUND==");
					
					Vec2D Size = {};
					Vec2D Pos = {};
					Vec2D Slice = {};
					CBackground* BG;

					for (UINT i = 0; i < (UINT)BG_TYPE::END; ++i)
					{
						fwscanf_s(pFile, L"%f%f%f%f%f%f", &Size.x, &Size.y, &Pos.x, &Pos.y, &Slice.x, &Slice.y);
						BG = curStg->GetBG(static_cast<BG_TYPE>(i));
						BG->SetAtlas(tex);
						BG->SetScale(Size);
						BG->SetAtlasInfo(true, Pos, Slice);
					}
					tex = nullptr;

					do { fwscanf_s(pFile, L"%s", szReadBuff, 256); } while (wstring(szReadBuff) == L"==PLATFORM==");
					CPlatform* PLT;

					for (UINT i = 0; i < (UINT)PLT_TYPE::END; ++i)
					{
						fwscanf_s(pFile, L"%s", szReadBuff, 256);
						fwscanf_s(pFile, L"%s", szReadBuff, 256);
						tex = CResourceMgr::GetInst()->LoadTexture(EP + L"_" + STG + L"_PLT" + std::to_wstring(i), szReadBuff);
						PLT = curStg->GetPLT(static_cast<PLT_TYPE>(i));
						PLT->SetTexture(tex);
					}
					tex = nullptr;

					do { fwscanf_s(pFile, L"%s", szReadBuff, 256); } while (wstring(szReadBuff) == L"==OBSTACLE==");
					CObstacle* OBS;
					for (UINT i = 0; i < (UINT)OBS_TYPE::END; ++i)
					{
						fwscanf_s(pFile, L"%s", szReadBuff, 256);
						fwscanf_s(pFile, L"%s", szReadBuff, 256);
						if (i == 2) // JUMP_UP
						{

						}
						else if (i == 7) // DBJUMP_UP
						{

						}

						tex = CResourceMgr::GetInst()->LoadTexture(EP + L"_" + STG + L"_OBS" + std::to_wstring(i), szReadBuff);
					}
					
					
				}
			}
		}
	}
}
