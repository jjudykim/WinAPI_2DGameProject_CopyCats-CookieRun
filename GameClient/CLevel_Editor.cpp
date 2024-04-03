#include "pch.h"
#include "CLevel_Editor.h"

#include "resource.h"
#include "CEngine.h"

#include "CPathMgr.h"
#include "CLevelMgr.h"
#include "CStageMgr.h"
#include "CResourceMgr.h"
#include "CTaskMgr.h"
#include "CMouseMgr.h"
#include "CHandleMgr.h"
#include "CCamera.h"

#include "CObject.h"
#include "CTexture.h"
#include "CDraw.h"
#include "CAnimator.h"
#include "CStage.h"
#include "CObstacle.h"
#include "CPlatform.h"


HBITMAP ResizeBitmap(HBITMAP hBmp, int width, int height);

// For Animation Editor ============================
// global
wstring g_DialogText = L"";

// 0 ~ 9 : Edit Control, 10 ~ 19 : Spin Control 
HWND g_hDrawEdit[20] = {};

HWND g_DrawCtrl = nullptr;
RECT g_DrawSize = {};

// For Stage Editor ================================
CObject* SelectObj = nullptr;


CLevel_Editor::CLevel_Editor()
	: m_hMenu(nullptr)
	, m_EditTex(nullptr)
	, m_EditAnim(nullptr)
	, m_CurDraw(nullptr)
	, m_PrevDraw(nullptr)
	, m_Drawable(false)
	, m_Drawing(false)
	, m_CreatingAnim(false)
	, m_PlayingAnim(false)
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
				Vec2D MousePos = CMouseMgr::GetInst()->GetMouseDownPos();
				pObject->SetPos(CCamera::GetInst()->GetRealPos(MousePos));
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
				m_PrevDraw = m_CurDraw;

				// 그린 Draw 객체의 정보들을 이용해서 Edit Control 값들 세팅
				wchar_t szBuff[256] = {};
				AniFrm frm = {};

				if (g_hDrawEdit != NULL)
				{
					swprintf_s(szBuff, 256, L"%.2f", m_CurDraw->GetPos().x + (m_CurDraw->GetScale().x / 2.f));
					SetWindowText(g_hDrawEdit[0], szBuff);
					frm.StartPos.x = (float)_wtof(szBuff);

					swprintf_s(szBuff, 256, L"%.2f", m_CurDraw->GetPos().y + (m_CurDraw->GetScale().y / 2.f));
					SetWindowText(g_hDrawEdit[1], szBuff);
					frm.StartPos.y = (float)_wtof(szBuff);

					swprintf_s(szBuff, 256, L"%.2f", m_CurDraw->GetScale().x);
					SetWindowText(g_hDrawEdit[2], szBuff);
					frm.SliceSize.x = (float)_wtof(szBuff);

					swprintf_s(szBuff, 256, L"%.2f", m_CurDraw->GetScale().y);
					SetWindowText(g_hDrawEdit[3], szBuff);
					frm.SliceSize.x = (float)_wtof(szBuff);

					SetWindowText(g_hDrawEdit[4], L"0.00");
					frm.Offset.x = 0.00f;
					SetWindowText(g_hDrawEdit[5], L"0.00");
					frm.Offset.y = 0.00f;

					m_CurFrm = frm;

					if (!m_CreatingAnim)
					{
						swprintf_s(szBuff, 256, L"%.2f", 0.0f);
						SetWindowText(g_hDrawEdit[6], szBuff);
						swprintf_s(szBuff, 256, L"%.2f", 0.0f);
						SetWindowText(g_hDrawEdit[7], szBuff);

						swprintf_s(szBuff, 256, L"%.2f", m_CurDraw->GetScale().x / 2.f);
						SetWindowText(g_hDrawEdit[8], szBuff);
						swprintf_s(szBuff, 256, L"%.2f", m_CurDraw->GetScale().y / 2.f);
						SetWindowText(g_hDrawEdit[9], szBuff);
					}
					if (g_DrawCtrl != NULL)
					{
						RedrawWindow(g_DrawCtrl, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
					}
				}

				m_Drawable = false;
				CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::CHANGE_CLICKABLE, false });
				m_CurDraw = nullptr;
			}
		}
	}
}

void CLevel_Editor::finaltick()
{
	if (m_EditAnim != nullptr && m_PlayingAnim)
	{
		if (m_EditAnim->IsFinish())
		{
			m_EditAnim->Reset();
		}

		m_EditAnim->finaltick();
	}
}

void CLevel_Editor::render()
{
	Vec2D texPos;
	texPos = CCamera::GetInst()->GetRenderPos(texPos);

	if (m_EditAnim != nullptr && m_PlayingAnim)
	{
		m_EditAnim->render(0);
	}
	else if (m_EditTex != nullptr)
	{
		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(DC, (int)texPos.x, (int)texPos.y
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

void CLevel_Editor::ResetAllAnimationOption()
{
	m_EditTex = nullptr;
	m_EditAnim = nullptr;
	m_CurDraw = nullptr;
	m_PrevDraw = nullptr;
	m_Drawing = false;
	m_Drawable = false;
	m_CreatingAnim = false;
	m_PlayingAnim = false;	
}

void CLevel_Editor::Exit()
{
}


vector<wstring> CLevel_Editor::GetLoadedTextureKey()
{
	vector<wstring> vKey;

	const map<wstring, CTexture*>& tMap = CResourceMgr::GetInst()->m_mapTex;
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
			if (CResourceMgr::GetInst()->FindTexture(szBuff) != nullptr)
			{
				MessageBox(nullptr, szBuff, L"이미 존재하는 Texture입니다.", MB_OK);
			}
			else
			{
				g_DialogText = szBuff;
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
		// 로드된 텍스쳐 목록 불러오기
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
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDSELECT)
		{
			wchar_t szBuff[256] = {};
			int selectedIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);

			if (selectedIndex != LB_ERR)
			{
				SendMessage(hListBox, LB_GETTEXT, (WPARAM)selectedIndex, (LPARAM)szBuff);
			}

			// 선택된 텍스쳐 반영하면서 끄기
			g_DialogText = szBuff;
			//SetDlgItemText(hDlg, IDC_TEX, szBuff);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			g_DialogText = L"";
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

	HWND hEditAnim = CHandleMgr::GetInst()->FindHandle(IDD_EDITANIM);

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		if (hEditAnim == nullptr || hEditAnim == hDlg)
		{
			g_hDrawEdit[0] = GetDlgItem(hDlg, IDC_POSX);
			g_hDrawEdit[1] = GetDlgItem(hDlg, IDC_POSY);
			g_hDrawEdit[2] = GetDlgItem(hDlg, IDC_SIZEX);
			g_hDrawEdit[3] = GetDlgItem(hDlg, IDC_SIZEY);
			g_hDrawEdit[4] = GetDlgItem(hDlg, IDC_OFFSETX);
			g_hDrawEdit[5] = GetDlgItem(hDlg, IDC_OFFSETY);
			g_hDrawEdit[6] = GetDlgItem(hDlg, IDC_COLPOSX);
			g_hDrawEdit[7] = GetDlgItem(hDlg, IDC_COLPOSY);
			g_hDrawEdit[8] = GetDlgItem(hDlg, IDC_COLSIZEX);
			g_hDrawEdit[9] = GetDlgItem(hDlg, IDC_COLSIZEY);

			g_hDrawEdit[10] = GetDlgItem(hDlg, IDC_POSX_SPIN);
			g_hDrawEdit[11] = GetDlgItem(hDlg, IDC_POSY_SPIN);
			g_hDrawEdit[12] = GetDlgItem(hDlg, IDC_SIZEX_SPIN);
			g_hDrawEdit[13] = GetDlgItem(hDlg, IDC_SIZEY_SPIN);
			g_hDrawEdit[14] = GetDlgItem(hDlg, IDC_OFFSETX_SPIN);
			g_hDrawEdit[15] = GetDlgItem(hDlg, IDC_OFFSETY_SPIN);
			g_hDrawEdit[16] = GetDlgItem(hDlg, IDC_COLPOSX_SPIN);
			g_hDrawEdit[17] = GetDlgItem(hDlg, IDC_COLPOSY_SPIN);
			g_hDrawEdit[18] = GetDlgItem(hDlg, IDC_COLSIZEX_SPIN);
			g_hDrawEdit[19] = GetDlgItem(hDlg, IDC_COLSIZEY_SPIN);

			for (int i = 0; i < 10; i++)
			{
				SendMessage(g_hDrawEdit[10 + i], UDM_GETBUDDY, (WPARAM)g_hDrawEdit[i], 0);
			}
		}
		else
		{
			g_DrawCtrl = GetDlgItem(hDlg, IDC_DRAW);
			RECT rect;
			GetWindowRect(g_DrawCtrl, &rect);
			MapWindowPoints(HWND_DESKTOP, CEngine::GetInst()->GetMainWnd(), (LPPOINT)&rect, 2);
			g_DrawSize = rect;
		}
	}
	return (INT_PTR)TRUE;
	break;

	case WM_NOTIFY:
	{
		HWND hEditAnim = CHandleMgr::GetInst()->FindHandle(IDD_EDITANIM);

		NMHDR* pNmhdr = (NMHDR*)lParam;
		for (int i = 10; i < 20; ++i)
		{
			if (pNmhdr->hwndFrom == g_hDrawEdit[i])
			{
				LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
				if (lpnmud->hdr.code == UDN_DELTAPOS)
				{
					wchar_t szBuff[256] = {};
					int newVal = 0;
					switch (i)
					{
					case 10:
					{
						GetDlgItemText(hEditAnim, IDC_POSX, szBuff, 256);
						float posX = (float)_wtof(szBuff);
						posX += ((float)lpnmud->iDelta * -1.f);
						swprintf_s(szBuff, 256, L"%.2f", posX);
						SetDlgItemText(hEditAnim, IDC_POSX, szBuff);
					}
					break;
					case 11:
					{
						GetDlgItemText(hEditAnim, IDC_POSY, szBuff, 256);
						float posY = (float)_wtof(szBuff);
						posY += ((float)lpnmud->iDelta * -1.f);
						swprintf_s(szBuff, 256, L"%.2f", posY);
						SetDlgItemText(hEditAnim, IDC_POSY, szBuff);
					}
					break;
					case 12:
					{
						GetDlgItemText(hEditAnim, IDC_SIZEX, szBuff, 256);
						float sizeX = (float)_wtof(szBuff);
						sizeX += ((float)lpnmud->iDelta * -1.f);
						swprintf_s(szBuff, 256, L"%.2f", sizeX);
						SetDlgItemText(hEditAnim, IDC_SIZEX, szBuff);
					}
					break;
					case 13:
					{
						GetDlgItemText(hEditAnim, IDC_SIZEY, szBuff, 256);
						float sizeY = (float)_wtof(szBuff);
						sizeY += ((float)lpnmud->iDelta * -1.f);
						swprintf_s(szBuff, 256, L"%.2f", sizeY);
						SetDlgItemText(hEditAnim, IDC_SIZEY, szBuff);
					}
					break;
					case 14:
					{
						GetDlgItemText(hEditAnim, IDC_OFFSETX, szBuff, 256);
						float offsetX = (float)_wtof(szBuff);
						offsetX += ((float)lpnmud->iDelta * -1.f);
						swprintf_s(szBuff, 256, L"%.2f", offsetX);
						SetDlgItemText(hEditAnim, IDC_OFFSETX, szBuff);
					}
					break;
					case 15:
					{
						GetDlgItemText(hEditAnim, IDC_OFFSETY, szBuff, 256);
						float offsetY = (float)_wtof(szBuff);
						offsetY += ((float)lpnmud->iDelta * -1.f);
						swprintf_s(szBuff, 256, L"%.2f", offsetY);
						SetDlgItemText(hEditAnim, IDC_OFFSETY, szBuff);
					}
					break;
					case 16:
					{
						GetDlgItemText(hEditAnim, IDC_COLPOSX, szBuff, 256);
						float colPosX = (float)_wtof(szBuff);
						colPosX += ((float)lpnmud->iDelta * -1.f);
						swprintf_s(szBuff, 256, L"%.2f", colPosX);
						SetDlgItemText(hEditAnim, IDC_COLPOSX, szBuff);
					}
					break;
					case 17:
					{
						GetDlgItemText(hEditAnim, IDC_COLPOSY, szBuff, 256);
						float colPosY = (float)_wtof(szBuff);
						colPosY += ((float)lpnmud->iDelta * -1.f);
						swprintf_s(szBuff, 256, L"%.2f", colPosY);
						SetDlgItemText(hEditAnim, IDC_COLPOSY, szBuff);
					}
					break;
					case 18:
					{
						GetDlgItemText(hEditAnim, IDC_COLSIZEX, szBuff, 256);
						float colSizeX = (float)_wtof(szBuff);
						colSizeX += ((float)lpnmud->iDelta * -1.f);
						swprintf_s(szBuff, 256, L"%.2f", colSizeX);
						SetDlgItemText(hEditAnim, IDC_COLSIZEX, szBuff);
					}
					break;
					case 19:
					{
						GetDlgItemText(hEditAnim, IDC_COLSIZEY, szBuff, 256);
						float colSizeY = (float)_wtof(szBuff);
						colSizeY += ((float)lpnmud->iDelta * -1.f);
						swprintf_s(szBuff, 256, L"%.2f", colSizeY);
						SetDlgItemText(hEditAnim, IDC_COLSIZEY, szBuff);
					}
					break;
					}
				}
				break;
			}
		}
	}
	case WM_COMMAND:
	{
		HWND hEditAnim = CHandleMgr::GetInst()->FindHandle(IDD_EDITANIM);
		HWND hEditTex = CHandleMgr::GetInst()->FindHandle(IDD_EDITTEX);

		if (LOWORD(wParam) == IDPLAY)
		{
			CCamera::GetInst()->SetCameraDefault();
			pEditorLevel->SetPlayingAnimState(true);
		}
		if (LOWORD(wParam) == IDSTOP)
		{
			CCamera::GetInst()->SetCameraDefault();
			pEditorLevel->SetPlayingAnimState(false);
		}
		else if (LOWORD(wParam) == IDSAVE)
		{
			wchar_t szBuff[256] = {};
			GetDlgItemText(hEditAnim, IDC_FPS, szBuff, 256);
			float FPS = (float)_wtof(szBuff);
			pEditorLevel->GetEditAnim()->ConvertFPSToDuration(FPS);
			
			GetDlgItemText(hEditAnim, IDC_ANIM, szBuff, 256);
			OpenSaveFile(szBuff, L"anim");

			CHandleMgr::GetInst()->DeleteHandle(IDD_EDITANIM);
			CHandleMgr::GetInst()->DeleteHandle(IDD_EDITTEX);
			DestroyWindow(hEditAnim);
			DestroyWindow(hEditTex);
			CDraw* PrevDraw = pEditorLevel->GetPrevDraw();
			
			pEditorLevel->ResetAllAnimationOption();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			CHandleMgr::GetInst()->DeleteHandle(IDD_EDITANIM);
			CHandleMgr::GetInst()->DeleteHandle(IDD_EDITTEX);
			DestroyWindow(hEditAnim);
			DestroyWindow(hEditTex);
			
			pEditorLevel->ResetAllAnimationOption();
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == ID_TEXBTN)
		{
			DialogBox(CEngine::GetInst()->GetProcessInstance(),
				MAKEINTRESOURCE(IDD_TEXLIST),
				CEngine::GetInst()->GetMainWnd(), SelectTexProc);

			SetDlgItemText(hDlg, IDC_TEX, g_DialogText.c_str());
			pEditorLevel->SetEditTex(CResourceMgr::GetInst()->FindTexture(g_DialogText));
			CCamera::GetInst()->SetCameraDefault();
		}

		else if (LOWORD(wParam) == ID_ANIMBTN)
		{
			CDraw* PrevDraw = pEditorLevel->GetPrevDraw();
			if (PrevDraw)
			{
				CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::DELETE_OBJECT, (DWORD_PTR)PrevDraw });
			}

			if (OpenLoadFile(L"animation", L"anim"))
			{
				pEditorLevel->SetEditTex(pEditorLevel->GetEditAnim()->GetAtlas());
				AniFrm FirstFrm = pEditorLevel->GetEditAnim()->GetFrame(0);
				Vec2D ColPos = pEditorLevel->GetEditAnim()->GetColliderPos();
				Vec2D ColSize = pEditorLevel->GetEditAnim()->GetColliderSize();
				wchar_t szBuff[256] = {};

				swprintf_s(szBuff, 256, L"%s", pEditorLevel->GetEditTex()->GetKey().c_str());
				SetDlgItemText(hEditAnim, IDC_TEX, szBuff);
				swprintf_s(szBuff, 256, L"%s", pEditorLevel->GetEditAnim()->GetName().c_str());
				SetDlgItemText(hEditAnim, IDC_ANIM, szBuff);

				swprintf_s(szBuff, 256, L"%f", FirstFrm.Duration);
				float FPS = (0.5f / _wtof(szBuff));
				SetDlgItemInt(hEditAnim, IDC_FPS, FPS, true);

				swprintf_s(szBuff, 256, L"%d", pEditorLevel->GetEditAnim()->GetFrameCount());
				SetDlgItemInt(hEditAnim, IDC_MAXFRAME, _wtoi(szBuff), true);

				swprintf_s(szBuff, 256, L"%.2f", FirstFrm.StartPos.x);
				SetDlgItemText(hEditAnim, IDC_POSX, szBuff);
				swprintf_s(szBuff, 256, L"%.2f", FirstFrm.StartPos.y);
				SetDlgItemText(hEditAnim, IDC_POSY, szBuff);
				swprintf_s(szBuff, 256, L"%.2f", FirstFrm.SliceSize.x);
				SetDlgItemText(hEditAnim, IDC_SIZEX, szBuff);
				swprintf_s(szBuff, 256, L"%.2f", FirstFrm.SliceSize.y);
				SetDlgItemText(hEditAnim, IDC_SIZEY, szBuff);
				swprintf_s(szBuff, 256, L"%.2f", FirstFrm.Offset.x);
				SetDlgItemText(hEditAnim, IDC_OFFSETX, szBuff);
				swprintf_s(szBuff, 256, L"%.2f", FirstFrm.Offset.y);
				SetDlgItemText(hEditAnim, IDC_OFFSETY, szBuff);

				swprintf_s(szBuff, 256, L"%.2f", ColPos.x);
				SetDlgItemText(hEditAnim, IDC_COLPOSX, szBuff);
				swprintf_s(szBuff, 256, L"%.2f", ColPos.y);
				SetDlgItemText(hEditAnim, IDC_COLPOSY, szBuff);
				swprintf_s(szBuff, 256, L"%.2f", ColSize.x);
				SetDlgItemText(hEditAnim, IDC_COLSIZEX, szBuff);
				swprintf_s(szBuff, 256, L"%.2f", ColSize.y);
				SetDlgItemText(hEditAnim, IDC_COLSIZEY, szBuff);

				RedrawWindow(g_DrawCtrl, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
		}

		else if (LOWORD(wParam) == ID_LOWFRAME)
		{
			int FrameIndex = GetDlgItemInt(hEditAnim, IDC_FRAME, nullptr, true);
			if (0 <= FrameIndex - 1) --FrameIndex;
			SetDlgItemInt(hEditAnim, IDC_FRAME, FrameIndex, true);

			const AniFrm& curFrm = pEditorLevel->GetAnimFrm(FrameIndex);
			wchar_t szBuff[256] = {};

			swprintf_s(szBuff, 256, L"%.2f", curFrm.StartPos.x);
			SetDlgItemText(hEditAnim, IDC_POSX, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.StartPos.y);
			SetDlgItemText(hEditAnim, IDC_POSY, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.SliceSize.x);
			SetDlgItemText(hEditAnim, IDC_SIZEX, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.SliceSize.y);
			SetDlgItemText(hEditAnim, IDC_SIZEY, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.Offset.x);
			SetDlgItemText(hEditAnim, IDC_OFFSETX, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.Offset.y);
			SetDlgItemText(hEditAnim, IDC_OFFSETY, szBuff);

			RedrawWindow(g_DrawCtrl, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		}
		else if (LOWORD(wParam) == ID_HIGHFRAME)
		{
			int FrameIndex = GetDlgItemInt(hEditAnim, IDC_FRAME, nullptr, true);
			if (FrameIndex < pEditorLevel->GetEditAnim()->GetFrameCount() - 1)
			{
				++FrameIndex;
			}
			SetDlgItemInt(hEditAnim, IDC_FRAME, FrameIndex, true);

			const AniFrm& curFrm = pEditorLevel->GetAnimFrm(FrameIndex);
			wchar_t szBuff[256] = {};

			swprintf_s(szBuff, 256, L"%.2f", curFrm.StartPos.x);
			SetDlgItemText(hEditAnim, IDC_POSX, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.StartPos.y);
			SetDlgItemText(hEditAnim, IDC_POSY, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.SliceSize.x);
			SetDlgItemText(hEditAnim, IDC_SIZEX, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.SliceSize.y);
			SetDlgItemText(hEditAnim, IDC_SIZEY, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.Offset.x);
			SetDlgItemText(hEditAnim, IDC_OFFSETX, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.Offset.y);
			SetDlgItemText(hEditAnim, IDC_OFFSETY, szBuff);

			RedrawWindow(g_DrawCtrl, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		}
		else if (LOWORD(wParam) == ID_DIRECTDRAW)
		{
			if (hEditTex == nullptr) hEditTex = CHandleMgr::GetInst()->FindHandle(IDD_EDITTEX);

			if (pEditorLevel->GetEditTex() == nullptr)
			{
				MessageBox(CEngine::GetInst()->GetMainWnd(), L"편집할 텍스쳐를 먼저 선택해야 합니다.", L"경고", MB_OK);
				break;
			}

			CDraw* PrevDraw = pEditorLevel->GetPrevDraw();
			if (PrevDraw)
			{
				CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::DELETE_OBJECT, (DWORD_PTR)PrevDraw });
			}
			pEditorLevel->SetDrawable(true);
			CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::CHANGE_CLICKABLE, true });
			SetForegroundWindow(CEngine::GetInst()->GetMainWnd());
		}
		else if (LOWORD(wParam) == ID_APPLY)
		{
			if (hEditTex == nullptr) hEditTex = CHandleMgr::GetInst()->FindHandle(IDD_EDITTEX);
			if (pEditorLevel->GetEditTex() == nullptr)
			{
				MessageBox(CEngine::GetInst()->GetMainWnd(), L"편집할 텍스쳐를 먼저 선택해야 합니다.", L"경고", MB_OK);
				return TRUE;
			}
			int textLength = -1;
			for (int i = 0; i < 6; i++)
			{
				textLength = GetWindowTextLength(g_hDrawEdit[i]);
				if (textLength == 0)
				{
					MessageBox(CEngine::GetInst()->GetMainWnd(), L"데이터 수치가 입력되거나 직접 지정해야 합니다.", L"경고", MB_OK);
					return TRUE;
				}
			}

			RedrawWindow(g_DrawCtrl, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			AniFrm frm = {};

			wchar_t szBuff[256] = {};
			GetDlgItemText(hEditAnim, IDC_POSX, szBuff, 256);
			float PosX = (float)_wtof(szBuff);
			frm.StartPos.x = PosX;
			GetDlgItemText(hEditAnim, IDC_POSY, szBuff, 256);
			float PosY = (float)_wtof(szBuff);
			frm.StartPos.y = PosY;

			GetDlgItemText(hEditAnim, IDC_SIZEX, szBuff, 256);
			float SizeX = (float)_wtof(szBuff);
			frm.SliceSize.x = SizeX;
			GetDlgItemText(hEditAnim, IDC_SIZEY, szBuff, 256);
			float SizeY = (float)_wtof(szBuff);
			frm.SliceSize.y = SizeY;

			GetDlgItemText(hEditAnim, IDC_OFFSETX, szBuff, 256);
			float OffsetX = (float)_wtof(szBuff);
			frm.Offset.x = OffsetX;
			GetDlgItemText(hEditAnim, IDC_OFFSETY, szBuff, 256);
			float OffsetY = (float)_wtof(szBuff);
			frm.Offset.y = OffsetY;

			if (pEditorLevel->GetEditAnim() != nullptr)
			{
				GetDlgItemText(hEditAnim, IDC_COLPOSX, szBuff, 256);
				float ColPosX = (float)_wtof(szBuff);
				GetDlgItemText(hEditAnim, IDC_COLPOSY, szBuff, 256);
				float ColPosY = (float)_wtof(szBuff);
				GetDlgItemText(hEditAnim, IDC_COLSIZEX, szBuff, 256);
				float ColSizeX = (float)_wtof(szBuff);
				GetDlgItemText(hEditAnim, IDC_COLSIZEY, szBuff, 256);
				float ColSizeY = (float)_wtof(szBuff);

				pEditorLevel->GetEditAnim()->SetColliderInfo(Vec2D(ColPosX, ColPosY), Vec2D(ColSizeX, ColSizeY));
			}
			
			if (pEditorLevel->GetPrevDraw() != nullptr)
			{
				pEditorLevel->GetPrevDraw()->SetPos(Vec2D(PosX - (SizeX / 2.f), PosY - (SizeY / 2.f)));
				pEditorLevel->GetPrevDraw()->SetScale(Vec2D(SizeX, SizeY));
			}
			
			pEditorLevel->SetCurFrm(frm);
		}
		else if (LOWORD(wParam) == ID_ADDFRAME)
		{
			CAnimation* anim = pEditorLevel->GetEditAnim();

			wchar_t szBuff[256] = {};
			GetDlgItemText(hEditAnim, IDC_ANIM, szBuff, 256);
			if (szBuff[0] == L'\0')
			{
				MessageBox(CEngine::GetInst()->GetMainWnd(), L"애니메이션을 지정하거나 새로 생성해야 합니다.", L"경고", MB_OK);
				return TRUE;
			}
			wstring AnimName = szBuff;
			
			GetDlgItemText(hEditAnim, IDC_FPS, szBuff, 256);
			if (szBuff[0] != L'\0')
			{
				float FPS = (float)_wtof(szBuff);
				if (0.0f < FPS)
				{
					AniFrm curFrm = pEditorLevel->GetCurFrm();

					GetDlgItemText(hEditAnim, IDC_POSX, szBuff, 256);
					curFrm.StartPos.x = (float)_wtof(szBuff);
					GetDlgItemText(hEditAnim, IDC_POSY, szBuff, 256);
					curFrm.StartPos.y = (float)_wtof(szBuff);
					GetDlgItemText(hEditAnim, IDC_SIZEX, szBuff, 256);
					curFrm.SliceSize.x = (float)_wtof(szBuff);
					GetDlgItemText(hEditAnim, IDC_SIZEY, szBuff, 256);
					curFrm.SliceSize.y = (float)_wtof(szBuff);
					GetDlgItemText(hEditAnim, IDC_OFFSETX, szBuff, 256);
					curFrm.Offset.x = (float)_wtof(szBuff);
					GetDlgItemText(hEditAnim, IDC_OFFSETY, szBuff, 256);
					curFrm.Offset.y = (float)_wtof(szBuff);

					if (pEditorLevel->GetEditAnim() == nullptr)
					{
						anim = new CAnimation();
						anim->SetName(AnimName);
						anim->SetAtlasTexture(pEditorLevel->GetEditTex());
						
						pEditorLevel->SetEditAnim(anim);
					}

					int FPS = GetDlgItemInt(hEditAnim, IDC_FPS, nullptr, true);

					anim->AddAnimFrm(curFrm);
					pEditorLevel->GetEditAnim()->ConvertFPSToDuration(FPS);
					SetDlgItemInt(hEditAnim, IDC_MAXFRAME, anim->GetFrameCount(), true);
					SetDlgItemInt(hEditAnim, IDC_FRAME,anim->GetFrameCount() - 1, true);

					MessageBox(CEngine::GetInst()->GetMainWnd(), L"※ 애니메이션 프레임이 추가되었습니다 ※ \n", L"알림", MB_OK);

					
					pEditorLevel->SetCreatingAnimState(true);
					CDraw* PrevDraw = pEditorLevel->GetPrevDraw();
					if (PrevDraw)
					{
						CTaskMgr::GetInst()->AddTask(Task{ TASK_TYPE::DELETE_OBJECT, (DWORD_PTR)PrevDraw });
					}
					return TRUE;
				}
				else
				{
					MessageBox(CEngine::GetInst()->GetMainWnd(), L"애니메이션의 FPS를 다시 설정하세요 (0 이상, 높을수록 재생속도 빠름)", L"경고", MB_OK);
					delete anim;
					return TRUE;
				}
			}
			else
			{
				MessageBox(CEngine::GetInst()->GetMainWnd(), L"애니메이션의 FPS를 설정하세요 (0 이상, 높을수록 재생속도 빠름)", L"경고", MB_OK);
				return TRUE;
			}
		}
		else if (LOWORD(wParam) == ID_DELFRAME)
		{
			if (pEditorLevel->GetEditAnim()->GetFrameCount() < 1) return TRUE;
			else if (pEditorLevel->GetEditAnim()->GetFrameCount() == 1)
			{
				MessageBox(CEngine::GetInst()->GetMainWnd(), L"현재 애니메이션을 구성하는 마지막 프레임입니다", L"경고", MB_OK);
				return TRUE;
			}
			int index = GetDlgItemInt(hEditAnim, IDC_FRAME, nullptr, true);
			pEditorLevel->GetEditAnim()->DeleteFrm(index);
			if (index > 0) --index;
			
			SetDlgItemInt(hEditAnim, IDC_FRAME, index, true);
			SetDlgItemInt(hEditAnim, IDC_MAXFRAME, pEditorLevel->GetEditAnim()->GetFrameCount(), true);

			const AniFrm& curFrm = pEditorLevel->GetAnimFrm(index);
			wchar_t szBuff[256] = {};

			swprintf_s(szBuff, 256, L"%.2f", curFrm.StartPos.x);
			SetDlgItemText(hEditAnim, IDC_POSX, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.StartPos.y);
			SetDlgItemText(hEditAnim, IDC_POSY, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.SliceSize.x);
			SetDlgItemText(hEditAnim, IDC_SIZEX, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.SliceSize.y);
			SetDlgItemText(hEditAnim, IDC_SIZEY, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.Offset.x);
			SetDlgItemText(hEditAnim, IDC_OFFSETX, szBuff);
			swprintf_s(szBuff, 256, L"%.2f", curFrm.Offset.y);
			SetDlgItemText(hEditAnim, IDC_OFFSETY, szBuff);

			RedrawWindow(g_DrawCtrl, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		}
		break;
		
	}
		break;

	case WM_DRAWITEM:
	{
		if (g_DrawCtrl == nullptr) break;

		int destWidth = g_DrawSize.right - g_DrawSize.left;
		int destHeight = g_DrawSize.bottom - g_DrawSize.top;

		LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
		Graphics graphics(pDIS->hDC);

		graphics.Clear(Color(243, 243, 243));

		CTexture* curTex = pEditorLevel->GetEditTex();
		if (curTex == nullptr) break;

		wchar_t szBuff[256] = {};
		GetDlgItemText(hEditAnim, IDC_POSX, szBuff, 256);
		float srcX = (float)_wtof(szBuff);
		GetDlgItemText(hEditAnim, IDC_POSY, szBuff, 256);
		float srcY = (float)_wtof(szBuff);
		GetDlgItemText(hEditAnim, IDC_SIZEX, szBuff, 256);
		float srcWidth = (float)_wtof(szBuff);
		GetDlgItemText(hEditAnim, IDC_SIZEY, szBuff, 256);
		float srcHeight = (float)_wtof(szBuff);
		GetDlgItemText(hEditAnim, IDC_OFFSETX, szBuff, 256);
		float srcOffsetX = (float)_wtof(szBuff);
		GetDlgItemText(hEditAnim, IDC_OFFSETY, szBuff, 256);
		float srcOffsetY = (float)_wtof(szBuff);
		GetDlgItemText(hEditAnim, IDC_COLPOSX, szBuff, 256);
		float ColPosX = (float)_wtof(szBuff);
		GetDlgItemText(hEditAnim, IDC_COLPOSY, szBuff, 256);
		float ColPosY = (float)_wtof(szBuff);
		GetDlgItemText(hEditAnim, IDC_COLSIZEX, szBuff, 256);
		float ColSizeX = (float)_wtof(szBuff);
		GetDlgItemText(hEditAnim, IDC_COLSIZEY, szBuff, 256);
		float ColSizeY = (float)_wtof(szBuff);

		Image* image = new Image(curTex->GetFullPath().c_str());
		if (image && image->GetLastStatus() == Ok)
		{
			graphics.DrawImage(image, Rect(0, 0, destWidth, destHeight)
												, srcX - (srcWidth / 2.f) + srcOffsetX
												, srcY - (srcHeight / 2.f) + srcOffsetY
												, srcWidth, srcHeight, UnitPixel);

			float ratioX = destWidth / srcWidth;
			float ratioY = destHeight / srcHeight;

			Pen GreenPen(Color(255, 0, 255, 0));
			Pen RedPen(Color(255, 255, 0, 0));
			
			graphics.DrawRectangle(&RedPen, Rect(((srcWidth / 2 + ColPosX) - (ColSizeX / 2.f))* ratioX
												, ((srcHeight / 2 + ColPosY) - (ColSizeY / 2.f))* ratioY
												, ColSizeX * ratioX, ColSizeY * ratioY));
			graphics.DrawLine(&GreenPen, destWidth / 2, 0, destWidth / 2, destHeight);
			graphics.DrawLine(&GreenPen, 0, destHeight / 2, destWidth, destHeight / 2);
			

			delete image;
		}
		else
		{
			assert(nullptr); // 이미지 로드 실패 처리
		}

		return TRUE;
	}
		break;
	}

	

	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK EditStaticStgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
	assert(pEditorLevel);

	HWND hEditSTStage = CHandleMgr::GetInst()->FindHandle(IDD_EDITSTAGE_STATIC);
	HIMAGELIST hImageList = nullptr;
	HWND hWndListView = nullptr;

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hEditSTStage = CHandleMgr::GetInst()->FindHandle(IDD_EDITSTAGE_STATIC);

		HWND hCombo = GetDlgItem(hDlg, IDC_EPISODE);
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"EP1");
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"EP2");
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"EP3");
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"EP4");
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"EP5");
		SendMessage(hCombo, CB_SETCURSEL, (WPARAM)0, 0);

		hCombo = GetDlgItem(hDlg, IDC_STAGE);
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"STG1");
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"STG2");
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"STG3");
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"STG4");
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"STG5");
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"STG6");
		SendMessage(hCombo, CB_SETCURSEL, (WPARAM)0, 0);

		hCombo = GetDlgItem(hDlg, IDC_OBJTYPE);
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"OBSTACLE");
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"PLATFORM");

		return (INT_PTR)TRUE;
	}
		break;

	case WM_NOTIFY:
	{
		NMHDR* pNmhdr = (NMHDR*)lParam;
		for (int i = 10; i < 20; ++i)
		{
			if (pNmhdr->idFrom == IDC_LIST && pNmhdr->code == LVN_ITEMCHANGED)
			{
				NMLISTVIEW* pNMLV = (NMLISTVIEW*)lParam;
				if (pNMLV->uChanged & LVIF_STATE)
				{
					if ((pNMLV->uNewState & LVIS_SELECTED) && !(pNMLV->uOldState & LVIS_SELECTED))
					{
						wchar_t szBuff[256];
						ListView_GetItemText(pNmhdr->hwndFrom, pNMLV->iItem, 0, szBuff, sizeof(szBuff) / sizeof(szBuff[0]));
						SetDlgItemText(hDlg, IDC_SELECTOBJ, szBuff);
					}
				}
			}
		}
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_LOAD)
		{
			hImageList = ImageList_Create(64, 64,  ILC_COLOR32 | ILC_MASK, 4, 4);
			hWndListView = GetDlgItem(hDlg, IDC_LIST);
			ListView_DeleteAllItems(hWndListView);

			UINT Ep = SendMessage(GetDlgItem(hDlg, IDC_EPISODE), CB_SETCURSEL, (WPARAM)0, 0);
			UINT Stg = SendMessage(GetDlgItem(hDlg, IDC_STAGE), CB_SETCURSEL, (WPARAM)0, 0);
		
			wchar_t szBuff[256] = {};
			GetDlgItemText(hDlg, IDC_OBJTYPE, szBuff, 256);
			wstring Obj = szBuff;

			CStageMgr::GetInst()->LoadStageInfo(static_cast<EPISODE_TYPE>(Ep));
			CStage* EditStage = CStageMgr::GetInst()->GetStage(Ep, Stg);
			if (Obj == L"OBSTACLE")
			{
				CObstacle* curOBS;
				HICON hIcon;
				for (UINT i = 0; i < (UINT)OBS_TYPE::END; ++i)
				{
					curOBS = EditStage->GetOBS(static_cast<OBS_TYPE>(i));
					Bitmap* pBitmap = curOBS->GetTexture()->GetpBit();
					pBitmap->GetHICON(&hIcon);
					
					ImageList_ReplaceIcon(hImageList, -1, hIcon);
					DestroyIcon(hIcon);
				}
				ListView_SetImageList(hWndListView, hImageList, LVSIL_NORMAL);

				for (UINT i = 0; i < (UINT)OBS_TYPE::END; ++i)
				{
					wstring str = L"OBS_" + std::to_wstring(i);
					LV_ITEM lvItem;
					lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
					lvItem.iItem = i;
					lvItem.iSubItem = 0;
					lvItem.pszText = (LPWSTR)str.c_str();
					lvItem.iImage = i;

					ListView_InsertItem(hWndListView, &lvItem);
				}
			
			}
			else if (Obj == L"PLATFORM")
			{
				CPlatform* curPLT;
				HICON hIcon;
				for (UINT i = 0; i < (UINT)PLT_TYPE::END; ++i)
				{
					curPLT = EditStage->GetPLT(static_cast<PLT_TYPE>(i));
					Bitmap* pBitmap = curPLT->GetTexture()->GetpBit();
					pBitmap->GetHICON(&hIcon);

					ImageList_ReplaceIcon(hImageList, -1, hIcon);
					DestroyIcon(hIcon);
				}
				ListView_SetImageList(hWndListView, hImageList, LVSIL_NORMAL);

				for (UINT i = 0; i < (UINT)PLT_TYPE::END; ++i)
				{
					wstring str = L"PLT_" + std::to_wstring(i);
					LV_ITEM lvItem;
					lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
					lvItem.iItem = i;
					lvItem.iSubItem = 0;
					lvItem.pszText = (LPWSTR)str.c_str();
					lvItem.iImage = i;

					ListView_InsertItem(hWndListView, &lvItem);
				}
			}
			
			
		}
		else if (LOWORD(wParam) == IDSAVE)
		{
			
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			CHandleMgr::GetInst()->DeleteHandle(IDD_EDITSTAGE_STATIC);
			DestroyWindow(hEditSTStage);
			return (INT_PTR)TRUE;
		}
	}
		break;
	}
	return (INT_PTR)FALSE;
}

HBITMAP ResizeBitmap(HBITMAP hBmp, int width, int height)
{
	BITMAP bmp;
	GetObject(hBmp, sizeof(BITMAP), &bmp);

	HDC hDCSrc = CreateCompatibleDC(NULL);
	HDC hDCDst = CreateCompatibleDC(NULL);

	HBITMAP hBmpNew = CreateCompatibleBitmap(hDCSrc, width, height);

	HBITMAP hBmpOldSrc = (HBITMAP)SelectObject(hDCSrc, hBmp);
	HBITMAP hBmpOldDst = (HBITMAP)SelectObject(hDCDst, hBmpNew);

	SetStretchBltMode(hDCDst, HALFTONE); // 더 나은 이미지 품질을 위해
	StretchBlt(hDCDst, 0, 0, width, height, hDCSrc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

	SelectObject(hDCSrc, hBmpOldSrc);
	SelectObject(hDCDst, hBmpOldDst);

	DeleteDC(hDCSrc);
	DeleteDC(hDCDst);

	return hBmpNew;
}
	
void OpenSaveFile(wstring _Key, wstring _FileType)
{
	wchar_t szSelect[256] = {};
	int i = wcscpy_s(szSelect, 256, _Key.c_str());

	OPENFILENAME ofn = {};
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szSelect;
	ofn.nMaxFile = sizeof(szSelect);
	wstring filter = L"\0*." + _FileType;
	ofn.lpstrFilter = filter.c_str();
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;

	// 탐색창 초기 위치 지정
	wstring strInitPath = CPathMgr::GetInst()->GetContentPath();
	strInitPath += L"animation\\";
	ofn.lpstrInitialDir = strInitPath.c_str();

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileName(&ofn))
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		if (_FileType == L"anim")
		{
			wstring SelectedFilePath = L"animation\\";
			size_t FilePathPos = wstring(ofn.lpstrFile).find(SelectedFilePath);
			wstring SelectedFileName = wstring(ofn.lpstrFile).substr(FilePathPos + SelectedFilePath.length());
			SelectedFilePath += SelectedFileName;

			SelectedFileName = PathFindFileNameW(ofn.lpstrFile);               // 확장자 포함
			size_t pos = SelectedFileName.find(L".anim");
			SelectedFileName = SelectedFileName.substr(0, pos);

			CResourceMgr::GetInst()->SaveAnimation(pEditorLevel->GetEditAnim(), SelectedFileName, SelectedFilePath);
		}
		
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

	// 탐색창 초기 위치 지정
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

			wstring SelectedFilePath = L"texture\\";
			size_t FilePathPos = wstring(ofn.lpstrFile).find(SelectedFilePath);
			wstring SelectedFileName = wstring(ofn.lpstrFile).substr(FilePathPos + SelectedFilePath.length());
			SelectedFilePath += SelectedFileName;

			SelectedFileName = PathFindFileNameW(ofn.lpstrFile);               // 확장자 포함
			size_t pos = SelectedFileName.find(L".png");
			SelectedFileName = SelectedFileName.substr(0, pos);

			CResourceMgr::GetInst()->LoadTexture(g_DialogText, SelectedFilePath);
		}
		else if (_FileType == L"anim")
		{
			wstring SelectedFilePath = L"animation\\";
			size_t FilePathPos = wstring(ofn.lpstrFile).find(SelectedFilePath);
			wstring SelectedFileName = wstring(ofn.lpstrFile).substr(FilePathPos + SelectedFilePath.length());
			SelectedFilePath += SelectedFileName;

			SelectedFileName = PathFindFileNameW(ofn.lpstrFile);               // 확장자 포함
			size_t pos = SelectedFileName.find(L".anim");
			SelectedFileName = SelectedFileName.substr(0, pos);
			
			CAnimation* pAnim = CResourceMgr::GetInst()->LoadAnimation(SelectedFileName, SelectedFilePath);
			if (pAnim != nullptr)
			{
				CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
				CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
				assert(pEditorLevel);

				pEditorLevel->SetEditAnim(pAnim);
			}
		}
		return true;
	}

	return false;
}


