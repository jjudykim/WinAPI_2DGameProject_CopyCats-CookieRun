#include "pch.h"
#include "CPlayer.h"

#include "CEngine.h"
#include "CObject.h"

#include "CLevelMgr.h"
#include "CKeyMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
	: m_Speed(500.f)
	, m_PlayerImg(nullptr)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);

	m_Collider->SetName(L"Cookie's Collider");
	m_Collider->SetOffsetPos(Vec2D(13.5f, 70.f));
	m_Collider->SetScale(Vec2D(70.f, 135.f));

	COOKIE_INFO BraveCookie = { COOKIE_TYPE::BRAVE_COOKIE,
								Vec2D(270, 270), 2,
								L"texture\\BraveCookie_Atlas.png"};
	
	COOKIE_INFO AngelCookie = { COOKIE_TYPE::ANGEL_COOKIE,
								Vec2D(320, 320), 2,
								L"texture\\AngelCookie_Atlas.png" };

	COOKIE_INFO m_curCookie = BraveCookie;

	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerAtlasTex", m_curCookie._path);

	m_Animator->CreateAnimation(L"RUNNING", pAtlas, Vec2D(0.f + m_curCookie._dividerSize, m_curCookie._frmSize.y + m_curCookie._dividerSize * 2), 
														  Vec2D(m_curCookie._frmSize.x, m_curCookie._frmSize.y), m_curCookie._dividerSize, 4, 5);
	m_Animator->Play(L"RUNNING", true);

	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetMaxGravitySpeed(1000.f);
	m_RigidBody->SetJumpSpeed(400.f);
}

CPlayer::~CPlayer()
{
}


void CPlayer::begin()
{
}

void CPlayer::tick()
{
	CObject::tick();

	Vec2D vPos = GetPos();

	if (CKeyMgr::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::TAP)
	{
		m_RigidBody->Jump();
		LOG(LOG_TYPE::DBG_LOG, L"Player¿« Space Key")
	}
}

void CPlayer::render()
{
}

