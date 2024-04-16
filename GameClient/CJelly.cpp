#include "pch.h"
#include "CJelly.h"

#include "CLevelMgr.h"
#include "CPathMgr.h"
#include "CMouseMgr.h"
#include "CGameDataMgr.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CSound.h"
#include "CPlayer.h"
#include "CLevel.h"

CJelly::CJelly()
	: m_ObjType(DYNAMIC_OBJ_TYPE::END)
	, m_Index(0)
	, m_Value(0)
	, m_Texture(nullptr)
	, m_Sound(nullptr)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_MouseOn(false)
	, m_UseMouse(false)

{
	SetLayerType(LAYER_TYPE::JELLY);
	m_Animator = nullptr;
	m_Collider = (CCollider*)AddComponent(new CCollider);
}

CJelly::CJelly(const CJelly& _Other)
	: CObject(_Other)
	, m_ObjType(_Other.m_ObjType)
	, m_AtlasInfo(_Other.m_AtlasInfo)
	, m_Index(_Other.m_Index)
	, m_Value(_Other.m_Value)
	, m_Texture(_Other.m_Texture)
	, m_Sound(_Other.m_Sound)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
{
	if (_Other.m_Animator != nullptr)
	{
		m_Animator = GetComponent<CAnimator>();
	}
	m_Collider = GetComponent<CCollider>();
}

CJelly::~CJelly()
{

}

void CJelly::begin()
{
	m_Collider->SetScale(Vec2D(GetScale().x * 0.8f, GetScale().y * 0.8f));
}

void CJelly::tick()
{
	if (m_UseMouse)
	{
		CheckMouseOn();
	}
}

void CJelly::render()
{
	if (!(RENDER_MINPOSX <= (GetPos().x + GetScale().x) && GetPos().x - GetScale().x <= RENDER_MAXPOSX)) return;

	if (CLevelMgr::GetInst()->GetCurrentLevelType() != LEVEL_TYPE::EDITOR)
	{
		if (GetAnimator() != nullptr)
		{
			GetAnimator()->render();
			return;
		}
	}

	Vec2D vRenderPos = GetRenderPos();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC
		, (int)(vRenderPos.x - GetScale().x / 2.f), (int)(vRenderPos.y - GetScale().x / 2.f)
		, (int)GetScale().x, (int)GetScale().y
		, m_Texture->GetDC(), m_AtlasInfo.StartPos.x, m_AtlasInfo.StartPos.y
		, m_AtlasInfo.SliceSize.x, m_AtlasInfo.SliceSize.y
		, bf);
}

void CJelly::CheckMouseOn()
{
	Vec2D vPos = GetRenderPos();
	Vec2D vScale = GetScale();
	Vec2D vMousePos = CMouseMgr::GetInst()->GetMousePos();

	if (vPos.x - (vScale.x / 2.f) <= vMousePos.x
		&& vMousePos.x <= vPos.x + (vScale.x / 2.f)
		&& vPos.y - (vScale.y / 2.f) <= vMousePos.y
		&& vMousePos.y <= vPos.y + (vScale.x / 2.f))
	{
		m_MouseOn = true;
	}
	else
	{
		m_MouseOn = false;
	}
}

void CJelly::BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
	if (m_Sound != nullptr)
	{
		m_Sound->SetVolume(70.f);
		m_Sound->Play();
	}
	CPlayer* pCookie = static_cast<CPlayer*>(_OtherObj);

	CGameDataMgr::GetInst()->AddScore(m_Value);

	if (m_ObjType == DYNAMIC_OBJ_TYPE::COIN)
	{
		switch (m_Index)
		{
		case 5:
			CGameDataMgr::GetInst()->AddCoin(1);
			break;
		case 6:
			CGameDataMgr::GetInst()->AddCoin(10);
			break;
		case 7:
			CGameDataMgr::GetInst()->AddCoin(100);
			break;
		}
		
	}
	else if (m_ObjType == DYNAMIC_OBJ_TYPE::BONUSTIME)
	{
	}
	else if (m_ObjType == DYNAMIC_OBJ_TYPE::ITEM)
	{
		
		switch (m_Index)
		{
		case 17:       // SMALL_LIFE_POTION
			CGameDataMgr::GetInst()->AddHP(10);
			break;
		case 18:       // BIG_LIFE_POTION
			CGameDataMgr::GetInst()->AddHP(40);
			break;
		case 19:       // GET_MAGNETISM
			break;
		case 20:       // GET_DASH
			pCookie->TurnOnCookieState(COOKIE_COMPLEX_STATE::BOOST);
			break;
		case 21:       // GET_GIANT
			pCookie->TurnOnCookieState(COOKIE_COMPLEX_STATE::GIANT);
			break;
		case 22:       // GET_DASHWITHGIANT
			pCookie->TurnOnCookieState(COOKIE_COMPLEX_STATE::GIANT);
			pCookie->TurnOnCookieState(COOKIE_COMPLEX_STATE::BOOST);
			break;
		case 23:       // CHANGE_TO_COIN
			break;
		case 24:       // CHANGE_TO_BEAR
			break;
		case 25:       // CHANGE_TO_BONUSTIME
			break;
		}
	}

	_OtherObj->EndOverlap(_OtherCollider, this, _OwnCollider);
	Destroy();
}

void CJelly::EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
	
}

