#pragma once

class CEngine
{
SINGLE(CEngine);

private:
	HINSTANCE	m_hInstance;	// 프로세스 메모리 핸들
	HWND		m_hMainWnd;		// 메인 윈도우 핸들
	POINT		m_Resolution;	// 메인 윈도우 해상도
	HDC			m_hDC;			// 메인 윈도우 DC

public:
	int init(HINSTANCE _hInst, HWND _hWnd, POINT _Resolution);
	void progress();

public:
	HINSTANCE GetProcessInstance() { return m_hInstance; }
	HWND GetMainWnd() { return m_hMainWnd; }
	HDC GetMainDC() { return m_hDC; }

};

