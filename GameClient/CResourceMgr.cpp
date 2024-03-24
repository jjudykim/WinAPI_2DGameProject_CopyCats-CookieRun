#include "pch.h"
#include "CResourceMgr.h"

#include "CTexture.h"
#include "CAnimation.h"
#include "CPathMgr.h"

CResourceMgr::CResourceMgr()
{}

CResourceMgr::~CResourceMgr()
{
	Safe_Del_Map(m_mapTex);
	Safe_Del_Map(m_mapSound);
}

void CResourceMgr::init()
{
}

CTexture* CResourceMgr::LoadTexture(const wstring& _Key, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_Key);
	if (pTex != nullptr) { return pTex; }

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	if (FAILED(pTex->Load(strFilePath)))
	{
		LOG(LOG_TYPE::DBG_ERROR, L"텍스쳐 로딩 실패");
		delete pTex;

		return nullptr;
	}

	m_mapTex.insert(make_pair(_Key, pTex));
	pTex->m_Key = _Key;
	pTex->m_RelativePath = _strRelativePath;

	return pTex;
}

CTexture* CResourceMgr::CreateTexture(const wstring& _Key, UINT _Width, UINT _Height)
{
	// 해당 키로 등록된 텍스쳐가 있다면
	assert(!FindTexture(_Key));

	CTexture* pTex = new CTexture;
	if (FAILED(pTex->Create(_Width, _Height)))
	{
		MessageBox(nullptr, _Key.c_str(), L"텍스쳐 생성 실패", MB_OK);
		delete pTex;
		return nullptr;
	}

	m_mapTex.insert(make_pair(_Key, pTex));
	pTex->m_Key = _Key;

	return pTex;
	
}

CTexture* CResourceMgr::FindTexture(const wstring& _Key)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_Key);

	if (m_mapTex.end() == iter)
		return nullptr;

	return iter->second;
}

void CResourceMgr::SaveAnimation(CAnimation* _TargetAnim, const wstring& _Key, const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"w");

	if (pFile == nullptr)
	{
		return;
	}

	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");
	fwprintf_s(pFile, L"%s\n\n", _Key.c_str());

	fwprintf_s(pFile, L"[ATLAS_TEXTURE]\n");
	if ()

}

CAnimation* CResourceMgr::LoadAnimation(const wstring& _Key, const wstring& _strRelativePath)
{
	CAnimation* pAnim = FindAnimation(_Key);
	if (pAnim != nullptr) { return pAnim; }

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"r");

	pAnim = new CAnimation;
	if (nullptr == pFile)
	{
		delete pAnim;
		return nullptr;
	}

	wchar_t szReadBuff[256] = {};

	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		wstring strRead = szReadBuff;

		if (strRead == L"[ANIMATION_NAME]")
		{
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			pAnim->SetName(szReadBuff);
		}
		else if (strRead == L"[ATLAS_TEXTURE]")
		{
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			wstring strKey = szReadBuff;

			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			wstring strPath = szReadBuff;

			if (strKey != L"None" && strPath != L"None")
			{
				pAnim->m_Atlas = LoadTexture(strKey, strPath);
			}
		}
		else if (strRead == L"[COLLIDER_INFO]")
		{
			Vec2D ColliderInfo = {};

			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			fwscanf_s(pFile, L"%f%f", ColliderInfo.x, ColliderInfo.y);
			pAnim->m_ColliderInfo[0] = ColliderInfo;

			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			fwscanf_s(pFile, L"%f%f", ColliderInfo.x, ColliderInfo.y);
			pAnim->m_ColliderInfo[1] = ColliderInfo;
		}
		else if (strRead == L"[FRAME_COUNT]")
		{
			int frmCount = 0;
			fwscanf_s(pFile, L"%d", frmCount);

			for (int i = 0; i < frmCount; ++i)
			{
				AniFrm frm = {};

				do { fwscanf_s(pFile, L"%s", szReadBuff, 256); } 
				while (wcscmp(szReadBuff, L"[START_POS]"));

				fwscanf_s(pFile, L"%f%f", &frm.StartPos.x, &frm.StartPos.y);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f%f", &frm.SliceSize.x, &frm.SliceSize.y);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f%f", &frm.Offset.x, &frm.Offset.y);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f", &frm.Duration);

				pAnim->m_vecFrm.push_back(frm);
			}
		}
	}
	fclose(pFile);

	return pAnim;
}

CAnimation* CResourceMgr::FindAnimation(const wstring& _Key)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_Key);

	if (m_mapAnim.end() == iter)
		return nullptr;

	return iter->second;
}