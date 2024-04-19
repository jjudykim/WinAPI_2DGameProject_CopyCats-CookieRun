#include "pch.h"
#include "CObstacle.h"

#include "CLevelMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CMouseMgr.h"
#include "CTimeMgr.h"
#include "CTaskMgr.h"
#include "CSound.h"

CObstacle::CObstacle()
	: m_Texture(nullptr)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_Type(OBS_TYPE::END)
	, m_UseMouse(false)
	, m_MouseOn(false)
	, m_EffectSound(nullptr)
	, m_Acted(false)
	, m_Crash(false)
{
	SetLayerType(LAYER_TYPE::OBSTACLE);
	m_Animator = nullptr;
	m_Collider = (CCollider*)AddComponent(new CCollider);
}

CObstacle::CObstacle(const CObstacle& _Other)
	: CObject(_Other)
	, m_Type(_Other.m_Type)
	, m_Texture(_Other.m_Texture)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_EffectSound(_Other.m_EffectSound)
	, m_UseMouse(_Other.m_UseMouse)
	, m_MouseOn(false)
	, m_Acted(_Other.m_Acted)
{
	if (_Other.m_Animator != nullptr)
	{
		m_Animator = GetComponent<CAnimator>();
	}
	m_Collider = GetComponent<CCollider>();
}

CObstacle::~CObstacle()
{
}


void CObstacle::begin()
{
	m_Collider->SetScale(Vec2D(GetScale().x * 0.75f, GetScale().y));
}

void CObstacle::tick()
{
	if (m_UseMouse)
	{
		CheckMouseOn();
	}
	
	if (m_Crash)
	{
		Vec2D Definition = CCamera::GetInst()->GetRealPos(Vec2D(CEngine::GetInst()->GetResolution().x + 50.f, 70.f));

		Vec2D Direction = Definition - GetPos();
		Direction.Normalize();
		SetPos(GetPos() + (Direction * 1700.f * DT));
		if (Definition.x < GetPos().x)
		{
			Destroy();
		}

	}
}

void CObstacle::render()
{
	if (!(RENDER_MINPOSX <= (GetPos().x + GetScale().x) && GetPos().x - GetScale().x <= RENDER_MAXPOSX)) return;

	if (CLevelMgr::GetInst()->GetCurrentLevelType() != LEVEL_TYPE::EDITOR)
	{
		if (GetAnimator() != nullptr)
		{
			GetAnimator()->render(' ');
			return;
		}
	}

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	if (m_Type == OBS_TYPE::SLIDE_A || m_Type == OBS_TYPE::SLIDE_B)
	{
		AlphaBlend(DC
			, (int)(GetRenderPos().x - m_Texture->GetWidth() / 2.f)
			, (int)(GetRenderPos().y)
			, m_Texture->GetWidth(), m_Texture->GetHeight()
			, m_Texture->GetDC(), 0, 0
			, m_Texture->GetWidth(), m_Texture->GetHeight()
			, bf);
	}
	else
	{
		AlphaBlend(DC
			, (int)(GetRenderPos().x - m_Texture->GetWidth() / 2.f)
			, (int)(GetRenderPos().y - m_Texture->GetHeight())
			, m_Texture->GetWidth(), m_Texture->GetHeight()
			, m_Texture->GetDC(), 0, 0
			, m_Texture->GetWidth(), m_Texture->GetHeight()
			, bf);
	}
}

void CObstacle::ObstacleDownAction()
{
	/*if (600.f <= GetPos().y)
	{
		SetPos(GetPos().x, 600.f);
		m_EffectSound->Play();
	}
	else
	{
		obs->SetPos(Vec2D(obs->GetPos().x, obs->GetPos().y + (600 * DT * 4.f)));
		Vec2D check = obs->GetPos();
		int a = 0;
	}*/
}

void CObstacle::CheckMouseOn()
{
	Vec2D vPos = GetRenderPos();
	Vec2D vScale = GetScale();
	Vec2D vMousePos = CMouseMgr::GetInst()->GetMousePos();

	if (m_Type == OBS_TYPE::SLIDE_A || m_Type == OBS_TYPE::SLIDE_B)
	{
		if (vPos.x - (vScale.x / 2.f) <= vMousePos.x
			&& vMousePos.x <= vPos.x + (vScale.x / 2.f)
			&& vPos.y <= vMousePos.y
			&& vMousePos.y <= vPos.y + vScale.y)
		{
			m_MouseOn = true;
		}
		else
		{
			m_MouseOn = false;
		}
	}
	else
	{
		if (vPos.x - (vScale.x / 2.f) <= vMousePos.x
			&& vMousePos.x <= vPos.x + (vScale.x / 2.f)
			&& vPos.y - vScale.y <= vMousePos.y
			&& vMousePos.y <= vPos.y)
		{
			m_MouseOn = true;
		}
		else
		{
			m_MouseOn = false;
		}
	}
	
}

