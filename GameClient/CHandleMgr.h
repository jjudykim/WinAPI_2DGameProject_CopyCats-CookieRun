#pragma once
class CHandleMgr
{
	SINGLE(CHandleMgr);

private:
	map<int, HWND> m_mapHandle;

public:
	void init();
	void AddHandle(int, HWND);
	HWND FindHandle(const int& _Key);
};

