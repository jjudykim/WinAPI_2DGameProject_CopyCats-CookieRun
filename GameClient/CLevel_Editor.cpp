#include "pch.h"
#include "CLevel_Editor.h"

#include "resource.h"
#include "CEngine.h"

#include "CPathMgr.h"
#include "CLevelMgr.h"
#include "CAssetMgr.h"
#include "CTaskMgr.h"
#include "CMouseMgr.h"
#include "CCamera.h"

#include "CTexture.h"
#include "CDraw.h"


wstring tDialogText = L"";

CLevel_Editor::CLevel_Editor()
	: m_hMenu(nullptr)
	, m_EditTex(nullptr)
	, m_CurDraw(nullptr)
	, m_Drawable(false)
	, m_Drawing(false)
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
	CLevel::tick();

	if (m_Drawable)
	{
		if (!m_Drawing)
		{
			if (CMouseMgr::GetInst()->IsLbtnDowned())
			{
				m_Drawing = true;
				CObject* pObject = new CDraw;
				pObject->SetPos(CMouseMgr::GetInst()->GetMouseDownPos());
				pObject->SetScale(1, 1);
				AddObject(LAYER_TYPE::DRAW, pObject);
				m_CurDraw = dynamic_cast<CDraw*>(pObject);
				
			}
		}

		if (m_CurDraw != nullptr)
		{
			if (!m_CurDraw->IsDrawing())
			{
				m_Drawing = false;
				m_CurDraw = nullptr;
			}

		}
	}
}

void CLevel_Editor::render()
{
	Vec2D texPos;
	texPos = CCamera::GetInst()->GetRenderPos(texPos);

	if (m_EditTex!= nullptr)
	{
		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(DC, texPos.x, texPos.y
			, (int)m_EditTex->GetWidth(), (int)m_EditTex->GetHeight()
			, m_EditTex->GetDC(), 0, 0
			, (int)m_EditTex->GetWidth(), (int)m_EditTex->GetHeight(), bf);
	}

	CLevel::render();
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

INT_PTR CALLBACK CreateTexProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		
	}
	return (INT_PTR)TRUE;
	break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			wchar_t szBuff[256] = {};
			GetDlgItemText(hDlg, IDC_NEWTEX, szBuff, 256);
			if (CAssetMgr::GetInst()->FindTexture(szBuff) != nullptr)
			{
				MessageBox(nullptr, szBuff, L"�̹� �����ϴ� Texture�Դϴ�.", MB_OK);
			}
			else
			{
				tDialogText = szBuff;
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
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

// Dialog Procedure Function
INT_PTR CALLBACK SelectTexProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
	assert(pEditorLevel);
	
	HWND hListBox = GetDlgItem(hDlg, IDC_TEXLIST);

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		// �ε�� �ؽ��� ��� �ҷ�����
		const vector<wstring> &vKey = pEditorLevel->GetLoadedTextureKey();
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
			if (OpenLoadFile(L"texture", L"png"))
			{
				SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
				const vector<wstring>& vKey = pEditorLevel->GetLoadedTextureKey();
				for (size_t i = 0; i < vKey.size(); ++i)
				{
					SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)vKey[i].c_str());
				}
			}
			
		}
		else if (LOWORD(wParam) == IDSELECT)
		{
			wchar_t szBuff[256] = {};
			int selectedIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);

			if (selectedIndex != LB_ERR)
			{
				SendMessage(hListBox, LB_GETTEXT, (WPARAM)selectedIndex, (LPARAM)szBuff);
			}
			
			// ���õ� �ؽ��� �ݿ��ϸ鼭 ����
			tDialogText = szBuff;
			//SetDlgItemText(hDlg, IDC_TEX, szBuff);
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

		// ������ �ִϸ��̼� ��� �ҷ�����
	}
	return (INT_PTR)TRUE;
	break;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_LOADANIM)
		{
			OpenLoadFile(L"animation", L"anim");
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
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
	assert(pEditorLevel);

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{

	}
	return (INT_PTR)TRUE;
	break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDPLAY)
		{
		}
		else if (LOWORD(wParam) == IDSAVE)
		{

			DestroyWindow(hDlg);
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			DestroyWindow(hDlg);
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == ID_TEXBTN)
		{
			DialogBox(CEngine::GetInst()->GetProcessInstance(),
					  MAKEINTRESOURCE(IDD_TEXLIST),
				      CEngine::GetInst()->GetMainWnd(), SelectTexProc);

			SetDlgItemText(hDlg, IDC_TEX, tDialogText.c_str());
			pEditorLevel->SetEditTex(CAssetMgr::GetInst()->FindTexture(tDialogText));
			CCamera::GetInst()->SetCameraDefault();
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
			pEditorLevel->SetDrawable(true);
			CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::CHANGE_CLICKABLE, true });
			SetForegroundWindow(CEngine::GetInst()->GetMainWnd());
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
	
void OpenSaveFile(wstring _Path, wstring _FileType)
{
	wchar_t szSelect[256] = {};

	OPENFILENAME ofn = {};
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szSelect;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szSelect);
	wstring filter = L"\0*." + _FileType;
	ofn.lpstrFilter = filter.c_str();
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;

	// Ž��â �ʱ� ��ġ ����
	wstring strInitPath = CPathMgr::GetInst()->GetContentPath();
	strInitPath += (_Path + L"\\");
	ofn.lpstrInitialDir = strInitPath.c_str();

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileName(&ofn))
	{
		//m_EditTile->SaveToFile(szSelect);
	}
}


bool OpenLoadFile(wstring _Path, wstring _FileType)
{
	wchar_t szSelect[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szSelect;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szSelect);
	wstring filter = L"\0*." + _FileType;
	ofn.lpstrFilter = filter.c_str();
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;

	// Ž��â �ʱ� ��ġ ����
	wstring strInitPath = CPathMgr::GetInst()->GetContentPath();
	strInitPath += (_Path + L"\\");
	ofn.lpstrInitialDir = strInitPath.c_str();

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		if (_FileType == L"png")
		{
			DialogBox(CEngine::GetInst()->GetProcessInstance(),
				MAKEINTRESOURCE(IDD_ADDTEX),
				CEngine::GetInst()->GetMainWnd(), CreateTexProc);

			wstring SelectedFileName = L"texture\\";
			SelectedFileName += PathFindFileNameW(ofn.lpstrFile);
			CAssetMgr::GetInst()->LoadTexture(tDialogText, SelectedFileName);
		}
		
		return true;
	}

	return false;
}