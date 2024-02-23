#pragma once

class CEngine
{
SINGLE(CEngine);

private:
	HINSTANCE	m_hInstance;	// ���μ��� �޸� �ڵ�
	HWND		m_hMainWnd;		// ���� ������ �ڵ�
	POINT		m_Resolution;	// ���� ������ �ػ�
	HDC			m_hDC;			// ���� ������ DC

public:
	int init(HINSTANCE _hInst, HWND _hWnd, POINT _Resolution);
	void progress();

public:
	HINSTANCE GetProcessInstance() { return m_hInstance; }
	HWND GetMainWnd() { return m_hMainWnd; }
	HDC GetMainDC() { return m_hDC; }

};

