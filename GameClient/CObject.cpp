#include "pch.h"
#include "CObject.h"

#include "CEngine.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

void CObject::begin()
{
}

void CObject::tick()
{
}

void CObject::finaltick()
{
}

void CObject::render()
{
	HDC dc = CEngine::GetInst()->GetSubDC();

	Rectangle(dc, m_Pos.x - m_Scale.x * 0.5f
		, m_Pos.y - m_Scale.y * 0.5f
		, m_Pos.x + m_Scale.x * 0.5f
		, m_Pos.y + m_Scale.y * 0.5f);
}


