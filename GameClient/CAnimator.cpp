#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"
#include "CResourceMgr.h"

CAnimator::CAnimator()
	: m_CurAnim(nullptr)
	, m_Repeat(false)
{
}

CAnimator::CAnimator(const CAnimator& _Other)
	: CComponent(_Other)
	, m_CurAnim(nullptr)
	, m_Repeat(_Other.m_Repeat)
{
	for (const auto& pair : _Other.m_mapAnim)
	{
		CAnimation* pCloneAnim = pair.second->Clone();

		pCloneAnim->m_Animator = this;
		m_mapAnim.insert(make_pair(pair.first, pCloneAnim));
	}
	
	if (nullptr != _Other.m_CurAnim)
	{
		m_CurAnim = FindAnimation(_Other.m_CurAnim->GetName());
	}
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

void CAnimator::render(float)
{
	if (m_CurAnim != nullptr)
	{
		m_CurAnim->render(0.f);
	}
}

CAnimation* CAnimator::FindAnimation(const wstring& _AnimName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_AnimName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::LoadAnimation(const wstring& _Key, const wstring& _strRelativeFilePath)
{
	CAnimation* pNewAnim = CResourceMgr::GetInst()->LoadAnimation(_Key, _strRelativeFilePath);

	if (pNewAnim == nullptr)
	{
		delete pNewAnim;
		LOG(LOG_TYPE::DBG_ERROR, L"애니메이션 로딩 실패");
		return;
	}

	if (nullptr != FindAnimation(pNewAnim->GetName()))
	{
		delete pNewAnim;
		LOG(LOG_TYPE::DBG_ERROR, L"중복된 애니메이션");
		return;
	}

	pNewAnim->m_Animator = this;
	m_mapAnim.insert(make_pair(pNewAnim->GetName(), pNewAnim));
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
