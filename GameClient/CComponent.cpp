#include "pch.h"
#include "CComponent.h"

#include "CObject.h"

CComponent::CComponent()
	: m_Owner(nullptr)
{
}

CComponent::CComponent(const CComponent& _Other)
	: m_Owner(nullptr)
{
}

CComponent::~CComponent()
{
}
