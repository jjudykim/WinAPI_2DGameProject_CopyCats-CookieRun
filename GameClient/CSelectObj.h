#pragma once
class CSelectObj
{
private:
	HDC			m_DC;
	HGDIOBJ		m_hPrev;

public:
	CSelectObj(HDC _dc, HGDIOBJ _SelectedObj);
	~CSelectObj();
};

