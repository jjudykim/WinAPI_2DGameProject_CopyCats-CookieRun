#include "pch.h"
#include "CTimeMgr.h"
#include "CEngine.h"

float CTimeMgr::AccTime = 0.f;
wchar_t CTimeMgr::szBuff[255] = {};

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_FPS(0)
	, m_DeltaTime(0.f)
	, m_Time(0.f)
{
}

CTimeMgr::~CTimeMgr()
{}

void CTimeMgr::init()
{
	// 고성능 타이머의 주파수 조회
	QueryPerformanceFrequency(&m_llFrequency);

	// 고성능 카운터의 현재 값 조회
	QueryPerformanceCounter(&m_llCurCount);
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_DeltaTime = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;

	m_Time += m_DeltaTime;

	m_llPrevCount = m_llCurCount;
	
	++m_FPS;

	AccTime += m_DeltaTime;

	if (1.f < AccTime)
	{
		swprintf_s(szBuff, L"DeltaTime : %f, FPS : %d", m_DeltaTime, m_FPS);
		AccTime = 0.f;
		m_FPS = 0;
	}
}

void CTimeMgr::render()
{
	CEngine* pEngine = CEngine::GetInst();
	TextOut(pEngine->GetSubDC(), pEngine->GetResolution().x - 250, 10, szBuff, wcslen(szBuff));
}