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

}

void CPathMgr::GetParentPath(wchar_t* _Buffer)
{
}
