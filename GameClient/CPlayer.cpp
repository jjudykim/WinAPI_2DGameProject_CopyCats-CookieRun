#include "pch.h"
#include "CPlayer.h"

#include "CEngine.h"
#include "CObject.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
	: m_PlayerImg(nullptr)
{
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	COOKIE_INFO BraveCookie = { COOKIE_TYPE::BRAVE_COOKIE,
								Vec2D(270, 270), 2,
								L"texture\\BraveCookie_Atlas.png"};
	
	COOKIE_INFO AngelCookie = { COOKIE_TYPE::ANGLE_COOKIE,
								Vec2D(320, 320), 2,
								L"texture\\AngelCookie_Atlas.png" };

	COOKIE_INFO m_curCookie = AngelCookie;

	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerAtlasTex", m_curCookie._path);

	m_Animator->CreateAnimation(L"RUNNING", pAtlas, Vec2D(0.f + m_curCookie._dividerSize, m_curCookie._frmSize.y + m_curCookie._dividerSize * 2), 
														  Vec2D(m_curCookie._frmSize.x, m_curCookie._frmSize.y), m_curCookie._dividerSize, 4, 5);
	m_Animator->Play(L"RUNNING", true);
}

CPlayer::~CPlayer()
{
}


void CPlayer::begin()
{
}

void CPlayer::tick()
{
	Vec2D vPos = GetPos();

}

void CPlayer::render()
{
}

