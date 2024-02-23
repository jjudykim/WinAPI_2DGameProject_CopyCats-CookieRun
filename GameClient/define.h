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

#define USE_BRUSH(DC, TYPE) CSelectObj SelectBrush(DC, GetBrush(TYPE));