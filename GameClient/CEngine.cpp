#include "pch.h"

#include "CEngine.h"

#include "CTimeMgr.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_Resolution{}
	, m_hDC(nullptr)
{}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_hDC);
}

int CEngine::init(HINSTANCE _hInst, HWND _hWnd, POINT _Resolution)
{
	m_hInstance = _hInst;
	m_hMainWnd = _hWnd;
	m_Resolution = _Resolution;

	RECT wndRt = { 0, 0, m_Resolution.x, m_Resolution.y };
	AdjustWindowRect(&wndRt, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(m_hMainWnd, nullptr, 0, 0, wndRt.right - wndRt.left, wndRt.bottom - wndRt.top, 0);

	m_hDC = GetDC(m_hMainWnd);

	CTimeMgr::GetInst()->init();

	return S_OK;
}

void CEngine::progress()
{
	// ===============
	// Manager Tick
	// ===============
	CTimeMgr::GetInst()->tick();
}
