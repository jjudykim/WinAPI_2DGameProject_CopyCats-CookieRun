#include "pch.h"
#include "CJellyMgr.h"

#include "CJelly.h"
#include "CPathMgr.h"
#include "CAnimator.h"
#include "CLevelMgr.h"

CJellyMgr::CJellyMgr()
{
}

CJellyMgr::~CJellyMgr()
{
}

void CJellyMgr::init()
{
	CJelly* jelly = nullptr;
	int IndexCount = 0;

	for (UINT i = 0; i < (UINT)DYNAMIC_OBJ_TYPE::END; ++i)
	{
		switch (i)
		{
		case 0:        // Jelly
		{
			for (int j = 0; j < (UINT)JELLY_TYPE::END; ++j)
			{
				jelly = new CJelly;
				jelly->SetObjType(DYNAMIC_OBJ_TYPE::JELLY);
				jelly->SetIndex(IndexCount);
				m_arrJelly[i].push_back(jelly);
				++IndexCount;
			}
		}
		break;
		case 1:        // COIN
		{
			for (int j = 0; j < (UINT)COIN_TYPE::END; ++j)
			{
				jelly = new CJelly;
				jelly->SetObjType(DYNAMIC_OBJ_TYPE::COIN);
				jelly->SetIndex(IndexCount);
				m_arrJelly[i].push_back(jelly);
				++IndexCount;
			}
		}
		break;
		case 2:		   // BONUSTIME
		{
			for (int j = 0; j < (UINT)BONUSTIME_TYPE::END; ++j)
			{
				jelly = new CJelly;
				jelly->SetObjType(DYNAMIC_OBJ_TYPE::BONUSTIME);
				jelly->SetIndex(IndexCount);
				m_arrJelly[i].push_back(jelly);
				++IndexCount;
			}
		}
		break;
		case 3:        // ITEM
		{
			for (int j = 0; j < (UINT)ITEM_TYPE::END; ++j)
			{
				jelly = new CJelly;
				jelly->SetObjType(DYNAMIC_OBJ_TYPE::ITEM);
				jelly->SetIndex(IndexCount);
				m_arrJelly[i].push_back(jelly);
				++IndexCount;
			}
		}
		break;
		}
	}
}

void CJellyMgr::LoadJellyInfo()
{
	FILE* pFile = nullptr;
	wstring Path = CPathMgr::GetInst()->GetContentPath() + L"JellyInfo.info";

	_wfopen_s(&pFile, Path.c_str(), L"r");
	if (pFile == nullptr) { return; }

	CJelly* curJelly = nullptr;
	CTexture* tex = CResourceMgr::GetInst()->LoadTexture(L"Jellies_Atlas", L"texture\\Jellies_Atlas.png");
	CAnimator* pAnim = nullptr;
	AtlasInfo info = {};
	int value = 0;

	wchar_t szReadBuff[256] = {};
	
	UINT ObjType = 0;
	int index = 0;
	

	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		while (true)
		{
			if (wstring(szReadBuff) == L"[DYNAMIC_OBJ_TYPE]") break;
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
		}

		fwscanf_s(pFile, L"%s", szReadBuff, 256);
		if (wstring(szReadBuff) == L"JELLY") { ObjType = 0; }
		else if (wstring(szReadBuff) == L"COIN") { ObjType = 1; }
		else if (wstring(szReadBuff) == L"BONUSTIME") { ObjType = 2; }
		else if (wstring(szReadBuff) == L"ITEM") { ObjType = 3; }

		for (UINT i = 0; i < m_arrJelly[ObjType].size(); ++i)
		{
			do { fwscanf_s(pFile, L"%s", szReadBuff, 256); } while (wcscmp(szReadBuff, L"[TYPE_INDEX]"));
			//fwscanf_s(pFile, L"%s", szReadBuff, 256);
			fwscanf_s(pFile, L"%d", &index);
			curJelly = m_arrJelly[ObjType][i];
			curJelly->SetIndex(index);
			curJelly->SetTexture(tex);


			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			fwscanf_s(pFile, L"%f%f%f%f", &info.StartPos.x, &info.StartPos.y, &info.SliceSize.x, &info.SliceSize.y);
			if (ObjType == 0 && (i == 2 || i == 4))
			{
				curJelly->SetScale(info.SliceSize * 2.f);
			}
			else if (ObjType == 3 && i == 1)
			{
				curJelly->SetScale(info.SliceSize);
			}
			else curJelly->SetScale(info.SliceSize * 0.75f);

			curJelly->SetAtlasInfo(info);

			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			fwscanf_s(pFile, L"%s", szReadBuff, 256);

			if (wstring(szReadBuff) != L"NONE")
			{
				pAnim = (CAnimator*)curJelly->AddComponent(new CAnimator);
				wstring NameStr = L"Jelly_" + std::to_wstring(ObjType) + L"_" + std::to_wstring(index);
				pAnim->LoadAnimation(NameStr, szReadBuff);
				pAnim->Play(NameStr, true);
			}

			if (CLevelMgr::GetInst()->GetCurrentLevelType() == LEVEL_TYPE::GAME)
			{
				// Sound Set
				if (ObjType == 0)
				{
					if (index == 0) curJelly->SetSound(CResourceMgr::GetInst()->FindSound(L"Effect_GetNormalJelly"));
					else if (index == 1 || index == 3) curJelly->SetSound(CResourceMgr::GetInst()->FindSound(L"Effect_GetBearJelly"));
					else if (index == 2 || index == 4) curJelly->SetSound(CResourceMgr::GetInst()->FindSound(L"Effect_GetBigBearJelly"));
				}
				else if (ObjType == 1)
				{
					if (index == 0 || index == 1) curJelly->SetSound(CResourceMgr::GetInst()->FindSound(L"Effect_GetCoinJelly"));
					else if (index == 2) curJelly->SetSound(CResourceMgr::GetInst()->FindSound(L"Effect_GetBigCoinJelly"));
				}
				else if (ObjType == 2)
				{
					curJelly->SetSound(CResourceMgr::GetInst()->FindSound(L"Effect_GetAlphabetJelly"));
				}
				else if (ObjType == 3)
				{
					if (index == 0) curJelly->SetSound(CResourceMgr::GetInst()->FindSound(L"Effect_SmallEnergy"));
					else if (index == 1) curJelly->SetSound(CResourceMgr::GetInst()->FindSound(L"Effect_LargeEnergy"));
					else
					{
						curJelly->SetSound(CResourceMgr::GetInst()->FindSound(L"Effect_ItemJelly"));
					}
				}
			}

			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			fwscanf_s(pFile, L"%d", &value);
		}
	}

	LOG(LOG_TYPE::DBG_LOG, L"Jelly Dummy Create Success");

	fclose(pFile);
}

int CJellyMgr::CheckJellyData()
{
	for (UINT i = 0; i < (UINT)DYNAMIC_OBJ_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrJelly[i].size(); ++j)
		{
			CJelly* jelly = m_arrJelly[i][j];
			if (jelly == nullptr || jelly->GetSound() == nullptr || jelly->GetTexture() == nullptr)
			{
				LOG(LOG_TYPE::DBG_WARNING, L"Dynamic Object - Jelly Load 중 오류 발생");
				return false;
			}
		}
	}

	return true;
}
