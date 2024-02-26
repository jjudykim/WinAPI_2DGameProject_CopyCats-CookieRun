#include "pch.h"
#include "CAnimation.h"

CAnimation::CAnimation()
	: m_Animator(nullptr)
	, m_Time(0.f)
	, m_CurFrmIdx(0)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::finaltick()
{
}

void CAnimation::render()
{
}

