#include "pch.h"
#include "CSelectObj.h"

CSelectObj::CSelectObj(HDC _dc, HGDIOBJ _SelectedObj)
	: m_DC(_dc)
	, m_hPrev(nullptr)
{
	m_hPrev = SelectObject(m_DC, _SelectedObj);
}

CSelectObj::~CSelectObj()
{
	SelectObject(m_DC, m_hPrev);
}