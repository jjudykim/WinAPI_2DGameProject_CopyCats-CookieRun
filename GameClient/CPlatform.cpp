#include "pch.h"
#include "CPlatform.h"

#include "CCollider.h"

CPlatform::CPlatform()
{
	
}

CPlatform::CPlatform(Vec2D _Scale)
{
	CPlatform();
	SetScale(_Scale);
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());
}

CPlatform::~CPlatform()
{
}

void CPlatform::tick()
{
}

void CPlatform::BeginOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlatform::OnOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlatform::EndOverlap(CCollider* _OwnCollider, CObject* _OtherObj, CCollider* _OtherCollider)
{
}


