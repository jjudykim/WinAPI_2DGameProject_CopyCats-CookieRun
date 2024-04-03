#include "pch.h"
#include "CStage.h"

#include "CPathMgr.h"
#include "CBackground.h"
#include "CPlatform.h"
#include "CObstacle.h"

CStage::CStage()
{
	/*for (UINT i = 0; i < (UINT)BG_TYPE::END; ++i)
	{
		m_arrBG[i] = new CBackground;
		m_arrBG[i]->SetBGType(static_cast<BG_TYPE>(i));
	}
	
	for (UINT i = 0; i < (UINT)PLT_TYPE::END; ++i)
	{
		m_arrPLT[i] = new CPlatform;
		m_arrPLT[i]->SetPLTType(static_cast<PLT_TYPE>(i));
	}

	for (UINT i = 0; i < (UINT)OBS_TYPE::END; ++i)
	{
		m_arrOBS[i] = new CObstacle;
		m_arrOBS[i]->SetOBSType(static_cast<OBS_TYPE>(i));
	}*/
}

CStage::~CStage()
{
	m_vecStageInfo.clear();
}

void CStage::Enter()
{
}

void CStage::Exit()
{
}

int CStage::LoadFromFile()
{
	// LoadFromFile에서 진행되어야 할 일
	// 파일로부터 저장된 정보를 읽어들여 StageObjInfo를 작성

	// EP1_STG1_STObj.stg
	wstring FileName = L"EP" + std::to_wstring((UINT)m_EpisodeType + 1)
					+ L"_STG" + std::to_wstring((UINT)m_StageType + 1)
					+ L"_STObj.stg";

	wstring FilePath = CPathMgr::GetInst()->GetContentPath() + L"stage\\" + FileName;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, FilePath.c_str(), L"r");
	if (pFile == nullptr) { return E_FAIL; }

	wchar_t szReadBuff[256] = {};

	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		StageSTObjInfo tStageObj = {};

		if (wstring(szReadBuff) == L"[OBJECT_TYPE]")
		{
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			wstring strType = szReadBuff;
			if (strType == L"BACKGROUND") tStageObj._objType = LAYER_TYPE::BACKGROUND;
			else if (strType == L"PLATFORM") tStageObj._objType = LAYER_TYPE::PLATFORM;
			else if (strType == L"OBSTACLE") tStageObj._objType = LAYER_TYPE::OBSTACLE;
		}
		
		fwscanf_s(pFile, L"%s", szReadBuff, 256);
		if (wstring(szReadBuff) == L"[OBJECT_COUNT]")
		{
			int count = 0;
			fwscanf_s(pFile, L"%d", &count);

			for (int i = 0; i < count; ++i)
			{
				while (true)
				{
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
					if (wstring(szReadBuff) == L"[TYPE_INDEX]") break;
				}

				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				int index = 0;
				swscanf_s(szReadBuff, L"%d", &index);
				tStageObj._typeIndex = index;

				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f%f", &tStageObj._pos.x, &tStageObj._pos.y);

				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f%f", &tStageObj._scale.x, &tStageObj._scale.y);

				m_vecStageInfo.push_back(tStageObj);
			}
		}
	}

	fclose(pFile);

	return S_OK;
}


