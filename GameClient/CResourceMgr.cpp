#include "pch.h"
#include "CResourceMgr.h"

#include "CSound.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "CPathMgr.h"

CResourceMgr::CResourceMgr()
{}

CResourceMgr::~CResourceMgr()
{
	Safe_Del_Map(m_mapTex);
	Safe_Del_Map(m_mapSound);
	m_mapCookieInfo.clear();
	m_mapPetInfo.clear();
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

CTexture* CResourceMgr::CreateTexture(const wstring& _Key, UINT _Width, UINT _Height, bool _Alpha)
{
	// 해당 키로 등록된 텍스쳐가 있다면
	assert(!FindTexture(_Key));

	CTexture* pTex = new CTexture;
	int result;
	if (_Alpha == true)
	{
		result = pTex->CreateWithAlpha(_Width, _Height);
	}
	else
	{
		result = pTex->Create(_Width, _Height);
	}

	if (FAILED(result))
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

CSound* CResourceMgr::LoadSound(const wstring& _Key, const wstring& _strRelativePath)
{
	CSound* pSound = FindSound(_Key);
	if (nullptr != pSound)
	{
		return pSound;
	}

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pSound = new CSound;
	if (FAILED(pSound->Load(strFilePath)))
	{
		MessageBox(nullptr, _strRelativePath.c_str(), L"사운드 로딩 실패", MB_OK);
		delete pSound;
		return nullptr;
	}

	m_mapSound.insert(make_pair(_Key, pSound));

	pSound->m_Key = _Key;
	pSound->m_RelativePath = _strRelativePath;

	return pSound;
}


CSound* CResourceMgr::FindSound(const wstring& _Key)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_Key);

	if (m_mapSound.end() == iter)
		return nullptr;

	return iter->second;
}


void CResourceMgr::SaveAnimation(CAnimation* _TargetAnim, const wstring& _Key, const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath + L".anim";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"w");

	if (pFile == nullptr)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"애니메이션 저장 실패");
		return;
	}

	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");
	fwprintf_s(pFile, L"%s\n\n", _Key.c_str());

	fwprintf_s(pFile, L"[ATLAS_TEXTURE]\n");
	
	if (_TargetAnim->GetAtlas() == nullptr)
	{
		fwprintf_s(pFile, L"[ATLAS_KEY]\t%s\n", L"None");
		fwprintf_s(pFile, L"[ATLAS_PATH]\t%s\n", L"None");
	}
	else
	{
		fwprintf_s(pFile, L"[ATLAS_KEY]\t%s\n", _TargetAnim->GetAtlas()->GetKey().c_str());
		fwprintf_s(pFile, L"[ATLAS_PATH]\t%s\n", _TargetAnim->GetAtlas()->GetRelativePath().c_str());
	}
	fwprintf_s(pFile, L"\n");

	fwprintf_s(pFile, L"[COLLIDER_INFO]\n");
	if (_TargetAnim->GetColliderPos() != 0.f) fwprintf_s(pFile, L"[COLLIDER_POS]\t%f  %f\n", _TargetAnim->GetColliderPos().x , _TargetAnim->GetColliderPos().y);
	else fwprintf_s(pFile, L"[COLLIDER_POS]\t%f  %f\n", 0.0f, 0.0f);
	if (_TargetAnim->GetColliderSize() != 0.f) fwprintf_s(pFile, L"[COLLIDER_SIZE]\t%f  %f\n", _TargetAnim->GetColliderSize().x, _TargetAnim->GetColliderSize().y);
	else fwprintf_s(pFile, L"[COLLIDER_SIZE]\t%f  %f\n", 0.0f, 0.0f);

	fwprintf_s(pFile, L"\n\n");
	fwprintf_s(pFile, L"[FRAME_COUNT]\n");
	fwprintf_s(pFile, L"%d\n\n", _TargetAnim->GetFrameCount());

	// 각각의 프레임 정보를 저장
	for (int i = 0; i < _TargetAnim->GetFrameCount(); ++i)
	{
		AniFrm frm = _TargetAnim->GetFrame(i);
		fwprintf_s(pFile, L"[FRAME_INDEX]\t%d\n", i);
		fwprintf_s(pFile, L"[START_POS] \t%f  %f\n", frm.StartPos.x, frm.StartPos.y);
		fwprintf_s(pFile, L"[SLICE_SIZE]\t\t%f  %f\n", frm.SliceSize.x, frm.SliceSize.y);
		fwprintf_s(pFile, L"[OFFSET]\t\t%f  %f\n", frm.Offset.x, frm.Offset.y);
		fwprintf_s(pFile, L"[DURATION]  \t%f\n", frm.Duration);
		fwprintf_s(pFile, L"\n");
	}

	fclose(pFile);
}

CAnimation* CResourceMgr::LoadAnimation(const wstring& _Key, const wstring& _strRelativePath)
{
	CAnimation* pAnim = FindAnimation(_Key);
	if (pAnim != nullptr) { return pAnim; }

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	//strFilePath += L".anim";

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
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			fwscanf_s(pFile, L"%f%f", &pAnim->m_ColliderInfo[0].x, &pAnim->m_ColliderInfo[0].y);

			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			fwscanf_s(pFile, L"%f%f", &pAnim->m_ColliderInfo[1].x, &pAnim->m_ColliderInfo[1].y);
		}
		else if (strRead == L"[FRAME_COUNT]")
		{
			int frmCount = 0;
			fwscanf_s(pFile, L"%d", &frmCount);

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

	pAnim->SetName(_Key);
	m_mapAnim.insert(make_pair(_Key, pAnim));
	return pAnim;
}

CAnimation* CResourceMgr::FindAnimation(const wstring& _Key)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_Key);

	if (m_mapAnim.end() == iter)
		return nullptr;

	return iter->second;
}

void CResourceMgr::LoadCookieInfo()
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"CookieInfo.info";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"r");

	if (nullptr == pFile) { return; }

	wchar_t szReadBuff[256] = {};

	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		wstring strRead = szReadBuff;

		if (strRead == L"[COOKIE_COUNT]")
		{
			int Count = 0;
			fwscanf_s(pFile, L"%d", &Count);

			for (int i = 0; i < Count; ++i)
			{
				CookieInfo info = {};

				do { fwscanf_s(pFile, L"%s", szReadBuff, 256); }
				while (wcscmp(szReadBuff, L"[COOKIE_TYPE]"));
				int type = 0;
				fwscanf_s(pFile, L"%d", &type);
				info._type = static_cast<COOKIE_TYPE>(type);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f%f", &info._frmSize.x, &info._frmSize.y);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				wstring strRead = szReadBuff;
				info._nameStr = strRead;

				m_mapCookieInfo.insert(make_pair((UINT)info._type, info));
			}
		}
	}
	fclose(pFile);
}

CookieInfo CResourceMgr::FindCookieInfo(const UINT& _Key)
{
	map<UINT, CookieInfo>::iterator iter = m_mapCookieInfo.find(_Key);

	if (m_mapCookieInfo.end() == iter)
		return CookieInfo{};

	return iter->second;
}

void CResourceMgr::LoadPetInfo()
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"PetInfo.info";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"r");

	if (nullptr == pFile) { return; }

	wchar_t szReadBuff[256] = {};

	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		wstring strRead = szReadBuff;

		if (strRead == L"[PET_COUNT]")
		{
			int Count = 0;
			fwscanf_s(pFile, L"%d", &Count);

			for (int i = 0; i < Count; ++i)
			{
				PetInfo info = {};

				do { fwscanf_s(pFile, L"%s", szReadBuff, 256); } while (wcscmp(szReadBuff, L"[PET_TYPE]"));
				int type = 0;
				fwscanf_s(pFile, L"%d", &type);
				info._type = static_cast<PET_TYPE>(type);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f%f", &info._frmSize.x, &info._frmSize.y);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				wstring strRead = szReadBuff;
				info._nameStr = strRead;

				m_mapPetInfo.insert(make_pair((UINT)info._type, info));
			}
		}
	}
	fclose(pFile);
}

PetInfo CResourceMgr::FindPetInfo(const UINT& _Key)
{
	map<UINT, PetInfo>::iterator iter = m_mapPetInfo.find(_Key);

	if (m_mapPetInfo.end() == iter)
		return PetInfo{};

	return iter->second;
}

int CResourceMgr::CheckAllResource()
{
	// m_mapTex;
	map<wstring, CTexture*>::iterator texiter = m_mapTex.begin();
	for (; m_mapTex.end() != texiter; ++texiter)
	{
		if (texiter->second == nullptr) return false;
	}

	// m_mapSound;
	map<wstring, CSound*>::iterator waviter = m_mapSound.begin();
	for (; m_mapSound.end() != waviter; ++waviter)
	{
		if (waviter->second == nullptr) return false;
	}
	
	// m_mapAnim;
	map<wstring, CAnimation*>::iterator animiter = m_mapAnim.begin();
	for (; m_mapAnim.end() != animiter; ++animiter)
	{
		if (animiter->second == nullptr) return false;
	}

	return true;
}
