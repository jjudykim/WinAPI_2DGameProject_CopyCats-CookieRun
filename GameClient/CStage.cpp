#include "pch.h"
#include "CStage.h"

#include "CBackground.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	m_vecStageInfo.clear();
}

int CStage::LoadFromFile(const wstring& _FullPath)
{
	// LoadFromFile에서 진행되어야 할 일
	// 파일로부터 저장된 정보를 읽어들여 StageObjInfo를 작성

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _FullPath.c_str(), L"r");
	if (pFile == nullptr) { return E_FAIL; }

	wchar_t szReadBuff[256] = {};

	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		StageObjInfo tStageObj = {};

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
				do { fwscanf_s(pFile, L"%s", szReadBuff, 256); } while (wstring(szReadBuff) == L"[TYPE_INDEX]");

				fwscanf_s(pFile, L"%d", &tStageObj._typeIndex);

				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f%f", &tStageObj._startPos.x, &tStageObj._startPos.y);

				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f%f", &tStageObj._scale.x, &tStageObj._scale.y);

				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f", &tStageObj._speed);

				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				wstring str = szReadBuff;
				tStageObj._imageName = str;

				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				str = szReadBuff;
				tStageObj._path = str;

				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%d", &tStageObj._atlas);
				if (tStageObj._atlas)
				{
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
					fwscanf_s(pFile, L"%f%f", &tStageObj._slicePos.x, &tStageObj._slicePos.y);
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
					fwscanf_s(pFile, L"%f%f", &tStageObj._sliceSize.x, &tStageObj._sliceSize.y);
				}
				else
				{
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
					fwscanf_s(pFile, L"%s", szReadBuff, 256);
				}

				m_vecStageInfo.push_back(tStageObj);
			}
		}
	}

	fclose(pFile);

	return S_OK;
}


