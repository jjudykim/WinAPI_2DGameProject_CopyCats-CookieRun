#pragma once

#define _AFXDLL

// �̱��� ���� ����
#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						}\
						private:\
							type();\
							type(const type& _other) = delete;\
						public:\
							~type();

#define USE_PEN(DC, Type) CSelectObj SelectPen(DC, CEngine::GetInst()->GetPen(Type));
#define USE_BRUSH(DC, Type) CSelectObj SelectBrush(DC, CEngine::GetInst()->GetBrush(Type));

#define DT CTimeMgr::GetInst()->GetDeltaTime()
#define DC CEngine::GetInst()->GetSubDC()

#define LOG(Type, Msg) {\
							string FuncName = __FUNCTION__;\
							wstring strFuncName = wstring(FuncName.begin(), FuncName.end());\
							wchar_t szLog[256] = {};\
							swprintf_s(szLog, L"{%s : %d} : %s", strFuncName.c_str(), __LINE__, Msg);\
							DebugLog(Type, szLog);\
						}

#define CLONE(Type) virtual Type* Clone() override { return new Type(*this); }
#define CLONE_DISABLE(Type) virtual Type* Clone() override { return nullptr; }

#define GET_CUR_LEVEL CLevelMgr::GetInst()->GetCurrentLevel()
#define GET_CUR_LEVELTYPE CLevelMgr::GetInst()->GetCurrentLevelType()

#define RENDER_MINPOSX CCamera::GetInst()->GetLookAt().x - (CEngine::GetInst()->GetResolution().x / 2.f)
#define RENDER_MAXPOSX CCamera::GetInst()->GetLookAt().x + (CEngine::GetInst()->GetResolution().x / 2.f)

#define COOKIE_DEFAULT_POSX 0.f
#define COOKIE_DEFAULT_POSY 610.f

#define PET_DEFAULT_POSX -100.f
#define PET_DEFAULT_POSY 350.f

#define KEY_CHECK(Key, State) CKeyMgr::GetInst()->GetKeyState(Key) == State

#define KEY_TAP(Key)		KEY_CHECK(Key, KEY_STATE::TAP)
#define KEY_PRESSED(Key)	KEY_CHECK(Key, KEY_STATE::PRESSED)
#define KEY_RELEASED(Key)	KEY_CHECK(Key, KEY_STATE::RELEASED)
#define KEY_NONE(Key)		KEY_CHECK(Key, KEY_STATE::NONE)

#define TILE_SIZE 40