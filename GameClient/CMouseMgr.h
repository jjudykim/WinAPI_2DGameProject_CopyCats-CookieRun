#pragma once

class CMouseMgr
{
	SINGLE(CMouseMgr);

private:
	bool		  m_UseClick;

	Vec2D         m_MousePos;
	Vec2D         m_PrevMousePos;

	Vec2D		  m_MouseDownPos;
	Vec2D         m_DragDir;

	RECT		  m_ClickBoundary;
	bool		  m_UseBoundary;
	bool		  m_MouseLbtnDown;	

public:
	void init();
	void tick();

	

public:
	void LButtonDown();
	void LButtonUp();
	void LButtonClicked();

private:
	bool CheckMouseOnBoundary();

public:
	void SetClickRectBoundary(RECT _Boundary) { m_ClickBoundary = _Boundary; }
	void SetUseBoundary(bool _use) { m_UseBoundary = _use; }
	void SetUseClick(bool _use) { m_UseClick = _use; }

	void ResetMouse();
	Vec2D GetMousePos() { return m_MousePos; }
	Vec2D GetMouseDownPos() { return m_MouseDownPos; }
	bool IsLbtnDowned() { return m_MouseLbtnDown; }
	bool IsAbleClick() { return m_UseClick; }
};

