#include "pch.h"
#include "CJelly.h"

#include "CTexture.h"
#include "CPathMgr.h"
#include "CAnimator.h"

CJelly::CJelly()
{
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"JelliesAtlasTex", L"texture\\GeneralJellies_Atlas.png");
}

CJelly::~CJelly()
{

}

void CJelly::begin()
{
}

void CJelly::tick()
{
}

void CJelly::render()
{
}

