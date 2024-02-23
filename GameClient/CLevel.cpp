#include "pch.h"
#include "CLevel.h"
#include "CObject.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
	{
		delete m_vecObj[i];
	}
	
	m_vecObj.clear();
}

void CLevel::begin()
{
}

void CLevel::tick()
{
}

void CLevel::finaltick()
{
}

void CLevel::render()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
	{
		m_vecObj[i]->CObject::render();
	}
}


