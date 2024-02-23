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