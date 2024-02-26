#include "pch.h"

#include "CDbgRenderMgr.h"

#include "CEngine.h"
#include "CSelectObj.h"
#include "CTimeMgr.h"

CDbgRenderMgr::CDbgRenderMgr()
{
}

CDbgRenderMgr::~CDbgRenderMgr()
{
}

void CDbgRenderMgr::tick()
{
	
}

void CDbgRenderMgr::render()
{
	if (m_RenderList.empty())
		return;

	list<DbgRenderInfo>::iterator iter = m_RenderList.begin();

	for (; iter != m_RenderList.end(); )
	{
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);
		CSelectObj SelectPen(DC, CEngine::GetInst()->GetPen(iter->Color));

		if (DBG_SHAPE::RECT == iter->Shape)
		{
			Rectangle(DC, (int)(iter->Position.x - iter->Scale.x / 2.f)
				, (int)(iter->Position.y - iter->Scale.y / 2.f)
				, (int)(iter->Position.x + iter->Scale.x / 2.f)
				, (int)(iter->Position.y + iter->Scale.y / 2.f));
		}

		else if (DBG_SHAPE::CIRCLE == iter->Shape)
		{
			Ellipse(DC, (int)(iter->Position.x - iter->Scale.x / 2.f)
				, (int)(iter->Position.y - iter->Scale.y / 2.f)
				, (int)(iter->Position.x + iter->Scale.x / 2.f)
				, (int)(iter->Position.y + iter->Scale.y / 2.f));
		}

		else if (DBG_SHAPE::LINE == iter->Shape)
		{
			Vec2D vEndPos = iter->Position + iter->Scale;

			MoveToEx(DC, (int)iter->Position.x, (int)iter->Position.y, nullptr);
			LineTo(DC, (int)vEndPos.x, (int)vEndPos.y);
		}

		(*iter).Age += DT;
		if (iter->Duration < iter->Age) { iter = m_RenderList.erase(iter); }
		else { ++iter; }
	}

	if (m_LogList.empty())
		return;

	list<DbgLog>::iterator logiter = m_LogList.begin();

	SetBkMode(DC, TRANSPARENT);

	int i = 0;
	for (; logiter != m_LogList.end(); )
	{
		int yoffset = ((int)m_LogList.size() - (i + 1)) * m_LogSpace;

		switch (logiter->Type)
		{
		case LOG_TYPE::DBG_LOG:
			SetTextColor(DC, RGB(255, 255, 255));
			break;
		case LOG_TYPE::DBG_WARNING:
			SetTextColor(DC, RGB(240, 240, 20));
			break;
		case LOG_TYPE::DBG_ERROR:
			SetTextColor(DC, RGB(240, 20, 20));
			break;
		}

		TextOut(DC, (int)m_LogStartPos.x
			, (int)m_LogStartPos.y + yoffset
			, logiter->strLog.c_str()
			, (int)logiter->strLog.length());
	}

	logiter->Age += DT;
	if (m_LogLife <= logiter->Age) { logiter = m_LogList.erase(logiter); }
	else { ++logiter; }
	++i;

	SetBkMode(DC, OPAQUE);
	SetTextColor(DC, RGB(0, 0, 0));
}
