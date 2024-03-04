#include "pch.h"
#include "CAssetMgr.h"

#include "CTexture.h"
#include "CPathMgr.h"

CAssetMgr::CAssetMgr()
{}

CAssetMgr::~CAssetMgr()
{
	Safe_Del_Map(m_mapTex);
	Safe_Del_Map(m_mapSound);
}

void CAssetMgr::init()
{
}

CTexture* CAssetMgr::LoadTexture(const wstring& _Key, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_Key);
	if (pTex != nullptr) { return pTex; }

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	if (FAILED(pTex->Load(strFilePath)))
	{
		LOG(LOG_TYPE::DBG_ERROR, _strRelativePath.c_str(), L"텍스쳐 로딩 실패", MB_OK);
		delete pTex;

		return nullptr;
	}
	
	m_mapTex.insert(make_pair(_Key, pTex));
	pTex->m_Key = _Key;
	pTex->m_RelativePath = _strRelativePath;

	return pTex;
}

CTexture* CAssetMgr::FindTexture(const wstring& _Key)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_Key);

	if (m_mapTex.end() == iter)
		return nullptr;

	return iter->second;
}
