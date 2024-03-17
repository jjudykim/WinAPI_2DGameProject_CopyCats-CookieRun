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
		}
		else if (LOWORD(wParam) == ID_HIGHFRAME)
		{
		}

		else if (LOWORD(wParam) == ID_DIRECTDRAW)
		{
		}
		else if (LOWORD(wParam) == ID_APPLY)
		{
		}

		else if (LOWORD(wParam) == ID_LOWPOSX)
		{
		}
		else if (LOWORD(wParam) == ID_HIGHPOSX)
		{
		}
		else if (LOWORD(wParam) == ID_LOWPOSY)
		{
		}
		else if (LOWORD(wParam) == ID_HIGHPOSY)
		{
		}

		else if (LOWORD(wParam) == ID_LOWSIZEX)
		{
		}
		else if (LOWORD(wParam) == ID_HIGHSIZEX)
		{
		}
		else if (LOWORD(wParam) == ID_LOWSIZEY)
		{
		}
		else if (LOWORD(wParam) == ID_HIGHSIZEY)
		{
		}

		else if (LOWORD(wParam) == ID_LOWOFFSETX)
		{
		}
		else if (LOWORD(wParam) == ID_HIGHOFFSETX)
		{
		}
		else if (LOWORD(wParam) == ID_LOWOFFSETY)
		{
		}
		else if (LOWORD(wParam) == ID_HIGHOFFSETY)
		{
		}

		break;
	}
	return (INT_PTR)FALSE;
}
	
