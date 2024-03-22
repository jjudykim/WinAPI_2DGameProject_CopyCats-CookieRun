#include "pch.h"
#include "CHandleMgr.h"

CHandleMgr::CHandleMgr()
{}

CHandleMgr::~CHandleMgr()
{
	Safe_Del_Map(m_mapHandle);
}


void CHandleMgr::init()
{
}

void CHandleMgr::AddHandle(int _Key, HWND _Handle)
{
	m_mapHandle.insert(make_pair(_Key, _Handle));
}

HWND CHandleMgr::FindHandle(const int& _Key)
{
	map<int, HWND>::iterator iter = m_mapHandle.find(_Key);

	if (m_mapHandle.end() == iter)
		return nullptr;

	return iter->second;
}

void CHandleMgr::DeleteHandle(const int& _Key)
{
	m_mapHandle.erase(_Key);
}
