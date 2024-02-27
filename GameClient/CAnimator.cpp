#include "pch.h"
#include "CAnimator.h"

CAnimator::CAnimator()
	: m_CurAnim(nullptr)
{
}

CAnimator::~CAnimator()
{
	Safe_Del_Map(m_mapAnim);
}

void CAnimator::finaltick()
{
}

void CAnimator::render()
{
}

void CAnimator::CreateAnimation(const wstring& _AnimName, CTexture* _Atlas, Vec2D _StartPos, Vec2D _SliceSize, int _FrameCount, int _FPS)
{
}

CAnimation* CAnimator::FindAnimation(const wstring& _AnimName)
{
	return nullptr;
}

void CAnimator::LoadAnimation(const wstring& _strRelativeFilePath)
{
}

void CAnimator::Play(wstring& _AnimName, bool _Repeat)
{
}
