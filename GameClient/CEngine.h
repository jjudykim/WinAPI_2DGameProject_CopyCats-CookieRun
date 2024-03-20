#pragma once

class CEngine
{
SINGLE(CEngine);

private:
	HINSTANCE	m_hInstance;	// ���μ��� �޸� �ڵ�
	HWND		m_hMainWnd;		// ���� ������ �ڵ�
	POINT		m_Resolution;	// ���� ������ �ػ�
	HDC			m_hDC;			// ���� ������ DC

	HDC         m_hSubDC;       // ���� DC
	HBITMAP     m_hSubBitmap;   // ���� Bitmap

	HPEN        m_arrPen[(UINT)PEN_TYPE::END];
	HBRUSH      m_arrBrush[(UINT)BRUSH_TYPE::END];

	ULONG_PTR   m_gdiplusToken;

public:
	int init(HINSTANCE _hInst, HWND _hWnd, POINT _Resolution);
	void progress();

public:
	void CreateDefaultGDIObject();
	void ChangeWindowSize(Vec2D _Resolution, bool _bMenu);

public:
	HINSTANCE GetProcessInstance() { return m_hInstance; }
	
	HWND GetMainWnd() { return m_hMainWnd; }
	HDC GetMainDC() { return m_hDC; }
	HDC GetSubDC() { return m_hSubDC; }
	Vec2D GetResolution() { return m_Resolution; }

	HPEN GetPen(PEN_TYPE _type) { return m_arrPen[(UINT)_type]; }
	HBRUSH GetBrush(BRUSH_TYPE _type) { return m_arrBrush[(UINT)_type]; }
};

