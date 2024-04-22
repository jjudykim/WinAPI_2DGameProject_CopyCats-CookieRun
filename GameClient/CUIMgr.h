#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI*	m_FocusedUI;

public:
	CUI* GetFocusedUI() { return m_FocusedUI; }

public:
	void tick();

private:
	CUI* GetPriorityUI(CUI* _UI);
	void ChangeFocusedUI(CUI* _UI);
};

