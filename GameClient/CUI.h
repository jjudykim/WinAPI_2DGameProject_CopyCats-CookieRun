#pragma once
#include "CObject.h"

class CTexture;

class CUI
	: public CObject
{
private:
	CUI*			m_ParentUI;
	vector<CUI*>	m_vecChildUI;

	CTexture*		m_Tex;

	Vec2D			m_vFinalPos;
	RECT			m_Boundary;
	
	bool			m_MouseOn;
	bool			m_MouseLbtnDown;

public:
	virtual void tick() final;
	virtual void finaltick() final;
	virtual void render() final;

	virtual void tick_ui() = 0;
	virtual void render_ui();

private:
	virtual void CheckMouseOn();

	virtual void LButtonDown();
	virtual void LButtonClicked();

public:
	Vec2D GetFinalPos() { return m_vFinalPos; }
	CTexture* GetTexture() { return m_Tex; }
	const vector<CUI*>& GetChildUI() { return m_vecChildUI; }
	bool IsMouseOn() { return m_MouseOn; }
	bool IsLbtnDowned() { return m_MouseLbtnDown; }

	void SetTexture(CTexture* _tex) { m_Tex = _tex; }
	
	void AddChildUI(CUI* _UI)
	{
		m_vecChildUI.push_back(_UI);
		_UI->m_ParentUI = this;
	}
	

public:
	virtual CUI* Clone() = 0;
	CUI();
	CUI(const CUI& _Origin);
	~CUI();

	friend class CTaskMgr;
};

