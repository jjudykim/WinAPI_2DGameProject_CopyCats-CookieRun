#include "pch.h"
#include "CJelly.h"

#include "CLevelMgr.h"
#include "CPathMgr.h"
#include "CMouseMgr.h"
#include "CTexture.h"
#include "CSound.h"
#include "CAnimator.h"
#include "CCollider.h"

CJelly::CJelly()
	: m_ObjType(DYNAMIC_OBJ_TYPE::END)
	, m_Index(0)
	, m_Value(0)
	, m_Texture(nullptr)
	, m_Animator(nullptr)
	, m_Collider(nullptr)

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
	CSound* pSound = nullptr;

	if (m_ObjType == DYNAMIC_OBJ_TYPE::JELLY)
	{
		if (m_Index == 0) pSound = CResourceMgr::GetInst()->FindSound(L"Effect_GetNormalJelly");
		else if (m_Index == 1) pSound = CResourceMgr::GetInst()->FindSound(L"Effect_GetBearJelly");
		else if (m_Index == 2) pSound = CResourceMgr::GetInst()->FindSound(L"Effect_GetBigBearJelly");
		else if (m_Index == 3) pSound = CResourceMgr::GetInst()->FindSound(L"Effect_GetBearJelly");
		else if (m_Index = 4) pSound = CResourceMgr::GetInst()->FindSound(L"Effect_GetBigBearJelly");
	}
	else if (m_ObjType == DYNAMIC_OBJ_TYPE::COIN)
	{
		if (m_Index == 5 || m_Index == 6) pSound = CResourceMgr::GetInst()->FindSound(L"Effect_GetCoinJelly");
		else if (m_Index == 7) pSound = CResourceMgr::GetInst()->FindSound(L"Effect_GetBigCoinJelly");
	}
	else if (m_ObjType == DYNAMIC_OBJ_TYPE::BONUSTIME)
	{
		pSound = CResourceMgr::GetInst()->FindSound(L"Effect_GetAlphabetJelly");
	}
	else if (m_ObjType == DYNAMIC_OBJ_TYPE::ITEM)
	{
		if (m_Index == 0) pSound = CResourceMgr::GetInst()->FindSound(L"Effect_SmallEnergy");
		else if (m_Index == 1) pSound = CResourceMgr::GetInst()->FindSound(L"Effect_LargeEnergy");
		else pSound = CResourceMgr::GetInst()->FindSound(L"Effect_GetItemJelly");
	}

	pSound->SetVolume(50.f);
	pSound->Play();

	Destroy();
}

