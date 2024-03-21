#include "pch.h"
#include "CMouseMgr.h"

#include "CEngine.h"
#include "CKeyMgr.h"

CMouseMgr::CMouseMgr()
	: m_UseClick(false)
	, m_MouseLbtnDown(false)
	, m_ClickBoundary(RECT{})
	, m_MouseDownPos(Vec2D())
{
}

CMouseMgr::~CMouseMgr()
{
}

void CMouseMgr::init()
{
}

void CMouseMgr::tick()
{
	if (CEngine::GetInst()->GetMainWnd() == GetFocus())
	{
		// 마우스 좌표 계산
		m_PrevMousePos = m_MousePos;

		POINT ptMousePos = { };
		GetCursorPos(&ptMousePos);
		ScreenToClient(CEngine::GetInst()->GetMainWnd(), &ptMousePos);
		m_MousePos = ptMousePos;
		m_DragDir = m_MousePos - m_PrevMousePos;
	
		if (!m_UseClick) return;

		if (KEY_TAP(KEY::LBTN))
		{
			LButtonDown();
		}
		else if (KEY_RELEASED(KEY::LBTN))
		{
			if (m_MouseLbtnDown == true)
			{
				if (m_UseBoundary)
				{
					if (CheckMouseOnBoundary())
					{
						LButtonClicked();
					}
				}
				else if (!m_UseBoundary)
				{
					if (m_MouseDownPos != m_MousePos)
					{
						LButtonUp();
					}
					else
					{
						LButtonClicked();
					}
				}
				else
				{
					LButtonUp();
				}
			}
		}
	}
}

bool CMouseMgr::CheckMouseOnBoundary()
{
	bool isMouseOn = m_MousePos.x <= (float)m_ClickBoundary.right
					&& (float)m_ClickBoundary.left <= m_MousePos.x
					&& m_MousePos.y <= (float)m_ClickBoundary.bottom
					&& (float)m_ClickBoundary.top <= m_MousePos.y;

	return isMouseOn;
}

void CMouseMgr::ResetMouse()
{
	m_MouseLbtnDown = false;
	m_MouseDownPos = 0;
	m_MousePos = m_PrevMousePos;
}

void CMouseMgr::LButtonDown()
{
	m_MouseLbtnDown = true;
	m_MouseDownPos = m_MousePos;
	LOG(LOG_TYPE::DBG_WARNING, L"LButtonDown");
}

void CMouseMgr::LButtonUp()
{
	m_MouseLbtnDown = false;
	LOG(LOG_TYPE::DBG_LOG, L"LButtonUp");
}

void CMouseMgr::LButtonClicked()
{
	m_MouseLbtnDown = false;
	LOG(LOG_TYPE::DBG_ERROR, L"LButtonClicked");
}
