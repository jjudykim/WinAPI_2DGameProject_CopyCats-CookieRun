#include "pch.h"
#include "CPlayer.h"

#include "CEngine.h"
#include "CObject.h"

#include "CLevelMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
	: m_DoubleJumpCount(2)
	, m_CurJumpCount(0)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);

	m_Collider->SetName(L"Cookie's Collider");
	m_Collider->SetOffsetPos(Vec2D(13.5f, 70.f));
	m_Collider->SetScale(Vec2D(70.f, 135.f));

	CookieInfo BraveCookie = { COOKIE_TYPE::BRAVE_COOKIE,
								Vec2D(270, 270), 2,
								L"texture\\BraveCookie_Atlas.png"};
	
	CookieInfo AngelCookie = { COOKIE_TYPE::ANGEL_COOKIE,
								Vec2D(320, 320), 2,
								L"texture\\AngelCookie_Atlas.png" };

	CookieInfo m_curCookie = AngelCookie;

	CTexture* pAtlas = CResourceMgr::GetInst()->LoadTexture(L"PlayerAtlasTex", m_curCookie._path);

	m_Animator->CreateAnimation(L"RUNNING", pAtlas, Vec2D(0.f + m_curCookie._dividerSize, m_curCookie._frmSize.y + m_curCookie._dividerSize * 2), 
														  Vec2D(m_curCookie._frmSize.x, m_curCookie._frmSize.y), m_curCookie._dividerSize, 4, 5);
	m_Animator->Play(L"RUNNING", true);
}

CPlayer::~CPlayer()
{
}


void CPlayer::begin()
{
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&CPlayer::RestoreJumpCount);
}

void CPlayer::tick()
{
	CObject::tick();

	if (CKeyMgr::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
	{
		if (m_DoubleJumpCount > m_CurJumpCount)
		{
			m_RigidBody->Jump();
			m_CurJumpCount += 1;
		}
	}
}

void CPlayer::BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlayer::OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlayer::EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
}
