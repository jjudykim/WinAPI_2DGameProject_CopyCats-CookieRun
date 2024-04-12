#include "pch.h"
#include "CStage.h"

#include "CPathMgr.h"
#include "CTile.h"
#include "CBackground.h"
#include "CPlatform.h"
#include "CObstacle.h"

CStage::CStage()
	: m_DNObjTile(nullptr)
{
}

CStage::~CStage()
{
}

void CStage::Enter()
{
}

void CStage::Exit()
{
}

int CStage::LoadSTObjectsFromFile()
{
	// LoadFromFile에서 진행되어야 할 일
	// 파일로부터 저장된 정보를 읽어들여 StageObjInfo를 작성

	// ex) EP1_STG1_STObj.stg
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

				if(tStageObj._objType == LAYER_TYPE::BACKGROUND) m_vecSTObjInfo[0].push_back(tStageObj);
				else if (tStageObj._objType == LAYER_TYPE::PLATFORM) m_vecSTObjInfo[1].push_back(tStageObj);
				else if (tStageObj._objType == LAYER_TYPE::OBSTACLE) m_vecSTObjInfo[2].push_back(tStageObj);
			}
		}
	}

	fclose(pFile);

	LOG(LOG_TYPE::DBG_LOG, L"Static Object Loading Success");
	return S_OK;
}

int CStage::LoadDNObjectsFromFile()
{
	wstring FileName = L"EP" + std::to_wstring((UINT)m_EpisodeType + 1)
		+ L"_STG" + std::to_wstring((UINT)m_StageType + 1)
		+ L"_DNObj.stg";

	wstring FilePath = CPathMgr::GetInst()->GetContentPath() + L"stage\\" + FileName;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, FilePath.c_str(), L"r");
	if (pFile == nullptr) { return E_FAIL; }

	wchar_t szReadBuff[256] = {};
	UINT Col = 0;
	UINT Row = 0;

	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		while (true)
		{
			if (wstring(szReadBuff) == L"[COL]") break;
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
		}

		Row = 0;
		int index = 0;
		while (true)
		{
			fwscanf_s(pFile, L"%s", szReadBuff, 256);

			if (wstring(szReadBuff) == L"[END]") break;
			else index = std::stoi(szReadBuff);

			if (index != -1)
			{
				StageDNObjInfo info = {};
				if (index > 16)
				{
					info._objType = DYNAMIC_OBJ_TYPE::ITEM;
					info._typeIndex = index - 17;
				}
				else if (index > 7)
				{
					info._objType = DYNAMIC_OBJ_TYPE::BONUSTIME;
					info._typeIndex = index - 8;
				}
				else if (index > 4)
				{
					info._objType = DYNAMIC_OBJ_TYPE::COIN;
					info._typeIndex = index - 5;
				}
				else
				{
					info._objType = DYNAMIC_OBJ_TYPE::JELLY;
					info._typeIndex = index;
				}
				info._pos = Vec2D((int)Col * TILE_SIZE + (TILE_SIZE / 2.f), (int)Row * TILE_SIZE + (TILE_SIZE / 2.f));

				AddDNObjInfo(info);
			}
			++Row;
		}
		++Col;
	}
	
	fclose(pFile);

	LOG(LOG_TYPE::DBG_LOG, L"Dynamic Objects Load Success");
	return S_OK;
}


