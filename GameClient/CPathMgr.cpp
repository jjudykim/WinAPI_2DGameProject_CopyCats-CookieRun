#include "pch.h"
#include "resource.h"
#include "CPathMgr.h"

#include "CAnimation.h"
#include "CEngine.h"


CPathMgr::CPathMgr()
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::init()
{
	wchar_t szBuffer[256] = {};
	GetCurrentDirectory(256, szBuffer);
	GetParentPath(szBuffer);

	m_Content = szBuffer;
	m_Content = L"\\content\\";

	GetParentPath(szBuffer);
	m_Solution = szBuffer;

	wchar_t szProjName[50] = {};
	LoadStringW(CEngine::GetInst()->GetProcessInstance(), IDS_APP_TITLE, szProjName, 50);

	m_Proj = m_Solution + L"\\" + szProjName;
}

void CPathMgr::render()
{
	LOG(LOG_TYPE::DBG_LOG, m_Solution.c_str());
	LOG(LOG_TYPE::DBG_LOG, m_Proj.c_str());
	LOG(LOG_TYPE::DBG_LOG, m_Content.c_str());
}

void CPathMgr::GetParentPath(_Inout_ wchar_t* _Buffer)
{
	size_t len = wcslen(_Buffer);

	for (size_t i = len - 1; 0 < i; --i)
	{
		if (L'\\' == _Buffer[i])
		{
			_Buffer[i] = L'\0';
			break;
		}
	}
}
