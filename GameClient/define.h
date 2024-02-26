#pragma once

// ½Ì±ÛÅæ ÆÐÅÏ ±¸Çö
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

#define USE_PEN(DC, TYPE) CSelectObj SelectBrush(DC, CEngine::GetInst()->GetPen(TYPE));
#define USE_BRUSH(DC, TYPE) CSelectObj SelectBrush(DC, CEngine::GetInst()->GetBrush(TYPE));

#define DT CTimeMgr::GetInst()->GetDeltaTime()
#define DC CEngine::GetInst()->GetSubDC()

#define LOG(TYPE, Msg) {\
							string FuncName = __FUNCTION__;\
							wstring strFuncName = wstring(FuncName.begin(), FuncName.end());\
							wchar_t szLog[256] = {};\
							swprintf_s(szLog, L"{%s : %d} : %s", strFuncName.c_str(), __LINE__, Msg);\
							DebugLog(TYPE, szLog);\
						}
	
}