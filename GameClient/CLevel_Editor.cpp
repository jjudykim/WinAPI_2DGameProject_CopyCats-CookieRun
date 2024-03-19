#include "pch.h"
#include "CLevel_Editor.h"

#include "resource.h"
#include "CEngine.h"

#include "CLevelMgr.h"
#include "CAssetMgr.h"

CLevel_Editor::CLevel_Editor()
	: m_hMenu(nullptr)
{
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_GAMECLIENT));
}

CLevel_Editor::~CLevel_Editor()
{
}

void CLevel_Editor::begin()
{
}

void CLevel_Editor::tick()
{
}

void CLevel_Editor::Enter()
{
	SetMenu(CEngine::GetInst()->GetMainWnd(), m_hMenu);
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution(), true);

	// Test

}

void CLevel_Editor::Exit()
{
}


vector<wstring> CLevel_Editor::GetLoadedTextureKey()
{
	vector<wstring> vKey;

	const map<wstring, CTexture*>& tMap = CAssetMgr::GetInst()->m_mapTex;
	map<wstring, CTexture*>::const_iterator iter = tMap.begin();
	
	for (; iter != tMap.end(); ++iter)
	{
		vKey.push_back(iter->first);
	}

	return vKey;
}


// Dialog Procedure Function
INT_PTR CALLBACK SelectTexProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		// 로드된 텍스쳐 목록 불러오기
		HWND hListBox = GetDlgItem(hDlg, IDC_TEXLIST);
		vector<wstring> vKey = pEditorLevel->GetLoadedTextureKey();
		for (size_t i = 0; i < vKey.size(); ++i)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)vKey[i].c_str());
		}
	}
		return (INT_PTR)TRUE;
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_LOADTEX)
		{
		}
		else if (LOWORD(wParam) == IDSELECT)
		{
			// 선택된 텍스쳐 반영하면서 끄기
			wchar_t szBuff[256] = {};
			SetDlgItemText(hDlg, IDC_TEX, szBuff);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;

	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK SelectAnimProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		// 생성된 애니메이션 목록 불러오기
	}
	return (INT_PTR)TRUE;
	break;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_LOADANIM)
		{
		}
		else if (LOWORD(wParam) == IDSELECT)
		{
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}

	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK EditAnimProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		/*wstring Tex;
		wstring Anim;

		wchar_t szBuff[256] = {};
		GetDlgItemText(hDlg, IDC_TEX, szBuff, 256);
		Tex = szBuff;

		GetDlgItemText(hDlg, IDC_ANIM, szBuff, 256);
		Anim = szBuff;*/
	}
	return (INT_PTR)TRUE;
	break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDPLAY)
		{
		}
		else if (LOWORD(wParam) == IDSAVE)
		{

		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == ID_TEXBTN)
		{
			DialogBox(CEngine::GetInst()->GetProcessInstance(),
					  MAKEINTRESOURCE(IDD_TEXLIST),
				      CEngine::GetInst()->GetMainWnd(), SelectTexProc);
			break;
		}
		
		else if (LOWORD(wParam) == ID_ANIMBTN)
		{
			DialogBox(CEngine::GetInst()->GetProcessInstance(),
				MAKEINTRESOURCE(IDD_ANIMLIST),
				CEngine::GetInst()->GetMainWnd(), SelectAnimProc);
		}

		else if (LOWORD(wParam) == ID_LOWFRAME)
		{
			int Frame = GetDlgItemInt(hDlg, IDC_FRAME, nullptr, true);
			if (0 <= Frame - 1) --Frame;
			SetDlgItemInt(hDlg, IDC_FRAME, Frame, true);

		}
		else if (LOWORD(wParam) == ID_HIGHFRAME)
		{
			int Frame = GetDlgItemInt(hDlg, IDC_FRAME, nullptr, true);
			++Frame;
			SetDlgItemInt(hDlg, IDC_FRAME, Frame, true);
		}

		else if (LOWORD(wParam) == ID_DIRECTDRAW)
		{
			
		}
		else if (LOWORD(wParam) == ID_APPLY)
		{
		}

		else if (LOWORD(wParam) == ID_LOWPOSX)
		{
			wchar_t szBuff[256] = {};
			GetDlgItemText(hDlg, IDC_POSX, szBuff, 256);
			float posX = (float)_wtof(szBuff);
			posX -= 5.f;
			swprintf_s(szBuff, 256, L"%f", posX);
			SetDlgItemText(hDlg, IDC_POSX, szBuff);
			
		}
		else if (LOWORD(wParam) == ID_HIGHPOSX)
		{
			wchar_t szBuff[256] = {};
			GetDlgItemText(hDlg, IDC_POSX, szBuff, 256);
			float posX = (float)_wtof(szBuff);
			posX += 5.f;
			swprintf_s(szBuff, 256, L"%f", posX);
			SetDlgItemText(hDlg, IDC_POSX, szBuff);
		}
		else if (LOWORD(wParam) == ID_LOWPOSY)
		{
			wchar_t szBuff[256] = {};
			GetDlgItemText(hDlg, IDC_POSY, szBuff, 256);
			float posY = (float)_wtof(szBuff);
			posY -= 5.f;
			swprintf_s(szBuff, 256, L"%f", posY);
			SetDlgItemText(hDlg, IDC_POSY, szBuff);
		}
		else if (LOWORD(wParam) == ID_HIGHPOSY)
		{
			wchar_t szBuff[256] = {};
			GetDlgItemText(hDlg, IDC_POSY, szBuff, 256);
			float posY = (float)_wtof(szBuff);
			posY += 5.f;
			swprintf_s(szBuff, 256, L"%f", posY);
			SetDlgItemText(hDlg, IDC_POSY, szBuff);
		}

		else if (LOWORD(wParam) == ID_LOWSIZEX)
		{
			wchar_t szBuff[256] = {};
			GetDlgItemText(hDlg, IDC_SIZEX, szBuff, 256);
			float sizeX = (float)_wtof(szBuff);
			sizeX -= 5.f;
			swprintf_s(szBuff, 256, L"%f", sizeX);
			SetDlgItemText(hDlg, IDC_SIZEX, szBuff);
		}
		else if (LOWORD(wParam) == ID_HIGHSIZEX)
		{
			wchar_t szBuff[256] = {};
			GetDlgItemText(hDlg, IDC_SIZEX, szBuff, 256);
			float sizeX = (float)_wtof(szBuff);
			sizeX += 5.f;
			swprintf_s(szBuff, 256, L"%f", sizeX);
			SetDlgItemText(hDlg, IDC_SIZEX, szBuff);
		}
		else if (LOWORD(wParam) == ID_LOWSIZEY)
		{
			wchar_t szBuff[256] = {};
			GetDlgItemText(hDlg, IDC_SIZEY, szBuff, 256);
			float sizeY = (float)_wtof(szBuff);
			sizeY -= 5.f;
			swprintf_s(szBuff, 256, L"%f", sizeY);
			SetDlgItemText(hDlg, IDC_SIZEY, szBuff);
		}
		else if (LOWORD(wParam) == ID_HIGHSIZEY)
		{
			wchar_t szBuff[256] = {};
			GetDlgItemText(hDlg, IDC_SIZEY, szBuff, 256);
			float sizeY = (float)_wtof(szBuff);
			sizeY += 5.f;
			swprintf_s(szBuff, 256, L"%f", sizeY);
			SetDlgItemText(hDlg, IDC_SIZEY, szBuff);
		}

		else if (LOWORD(wParam) == ID_LOWOFFSETX)
		{
			wchar_t szBuff[256] = {};
			GetDlgItemText(hDlg, IDC_OFFSETX, szBuff, 256);
			float offsetX = (float)_wtof(szBuff);
			offsetX -= 5.f;
			swprintf_s(szBuff, 256, L"%f", offsetX);
			SetDlgItemText(hDlg, IDC_OFFSETX, szBuff);
		}
		else if (LOWORD(wParam) == ID_HIGHOFFSETX)
		{
			wchar_t szBuff[256] = {};
			GetDlgItemText(hDlg, IDC_OFFSETX, szBuff, 256);
			float offsetX = (float)_wtof(szBuff);
			offsetX += 5.f;
			swprintf_s(szBuff, 256, L"%f", offsetX);
			SetDlgItemText(hDlg, IDC_OFFSETX, szBuff);
		}
		else if (LOWORD(wParam) == ID_LOWOFFSETY)
		{
			wchar_t szBuff[256] = {};
			GetDlgItemText(hDlg, IDC_OFFSETY, szBuff, 256);
			float offsetY = (float)_wtof(szBuff);
			offsetY -= 5.f;
			swprintf_s(szBuff, 256, L"%f", offsetY);
			SetDlgItemText(hDlg, IDC_OFFSETY, szBuff);
		}
		else if (LOWORD(wParam) == ID_HIGHOFFSETY)
		{
			wchar_t szBuff[256] = {};
			GetDlgItemText(hDlg, IDC_OFFSETY, szBuff, 256);
			float offsetY = (float)_wtof(szBuff);
			offsetY += 5.f;
			swprintf_s(szBuff, 256, L"%f", offsetY);
			SetDlgItemText(hDlg, IDC_OFFSETY, szBuff);
		}

		break;
	}
	return (INT_PTR)FALSE;
}
	
