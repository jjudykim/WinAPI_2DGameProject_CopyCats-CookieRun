#include "pch.h"

#include "CEngine.h"

#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CDbgRenderMgr.h"
#include "CCollisionMgr.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_Resolution{}
	, m_hDC(nullptr)
	, m_arrPen{}
	, m_arrBrush{}
{}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_hDC);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	for (int i = 0; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		DeleteObject(m_arrBrush[i]);
	}
}

int CEngine::init(HINSTANCE _hInst, HWND _hWnd, POINT _Resolution)
{
	m_hInstance = _hInst;
	m_hMainWnd = _hWnd;
	m_Resolution = _Resolution;

	RECT wndRt = { 0, 0, m_Resolution.x, m_Resolution.y };
	AdjustWindowRect(&wndRt, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(m_hMainWnd, nullptr, 0, 0, wndRt.right - wndRt.left, wndRt.bottom - wndRt.top, 0);

	CreateDefaultGDIObject();

	// Manager initializing ========
	CPathMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();
	

	return S_OK;
}

void CEngine::progress()
{
	// ===============
	// Manager Tick
	// ===============
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();
	CDbgRenderMgr::GetInst()->tick();

	// ===============
	// Level Progress
	// ===============
	CLevelMgr::GetInst()->progress();
	CCollisionMgr::GetInst()->tick();

	// ===============
	// Render
	// ===============
	// Clear
	{
		USE_BRUSH(m_hSubDC, BRUSH_TYPE::BRUSH_GRAY);
		Rectangle(m_hSubDC, -1, -1, m_Resolution.x + 1, m_Resolution.y + 1);
	}

	CLevelMgr::GetInst()->render();
	CTimeMgr::GetInst()->render();
	CDbgRenderMgr::GetInst()->render();
	
	::BitBlt(m_hDC, 0, 0, m_Resolution.x, m_Resolution.y, m_hSubDC, 0, 0, SRCCOPY);
}

void CEngine::CreateDefaultGDIObject()
{
	m_hDC = ::GetDC(m_hMainWnd);

	m_hSubDC = ::CreateCompatibleDC(m_hDC);
	m_hSubBitmap = ::CreateCompatibleBitmap(m_hDC, m_Resolution.x, m_Resolution.y);

	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hSubDC, m_hSubBitmap);
	DeleteObject(hPrevBitmap);

	// PEN Set
	m_arrPen[(UINT)PEN_TYPE::PEN_RED] = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_GREEN] = ::CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_BLUE] = ::CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::PEN_BLACK] = ::CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	// BRUSH Set
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_RED] = ::CreateSolidBrush(RGB(255, 0, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_GREEN] = ::CreateSolidBrush(RGB(0, 255, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_BLUE] = ::CreateSolidBrush(RGB(0, 0, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_WHITE] = (HBRUSH)GetStockObject(WHITE_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_GRAY] = ::CreateSolidBrush(RGB(100, 100, 100));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

}
