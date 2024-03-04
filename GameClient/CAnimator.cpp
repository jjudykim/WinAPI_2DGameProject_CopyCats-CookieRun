#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
	: m_CurAnim(nullptr)
	, m_Repeat(false)
{
}

CAnimator::~CAnimator()
{
	Safe_Del_Map(m_mapAnim);
}

void CAnimator::finaltick()
{
	if (m_CurAnim != nullptr)
	{
		if (m_CurAnim->IsFinish() && m_Repeat)
		{
			m_CurAnim->Reset();
		}

		m_CurAnim->finaltick();
	}
}

void CAnimator::render()
{
	if (m_CurAnim != nullptr)
	{
		m_CurAnim->render();
	}
		
}

void CAnimator::CreateAnimation(const wstring& _AnimName, CTexture* _Atlas, Vec2D _StartPos, Vec2D _SliceSize, int _DividerSize, int _FrameCount, int _FPS)
{
	CAnimation* pAnim = FindAnimation(_AnimName);
	assert(!pAnim);

	pAnim = new CAnimation;
	pAnim->Create(_Atlas, _StartPos, _SliceSize, _DividerSize, _FrameCount, _FPS);
	pAnim->SetName(_AnimName);
	pAnim->m_Animator = this;
	m_mapAnim.insert(make_pair(_AnimName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _AnimName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_AnimName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::LoadAnimation(const wstring& _strRelativeFilePath)
{
}

void CAnimator::Play(const wstring& _AnimName, bool _Repeat)
{
	m_CurAnim = FindAnimation(_AnimName);

	if (m_CurAnim == nullptr)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"Play할 애니메이션을 찾을 수 없음");
		return;
	}

	m_CurAnim->Reset();
	m_Repeat = _Repeat;
}
