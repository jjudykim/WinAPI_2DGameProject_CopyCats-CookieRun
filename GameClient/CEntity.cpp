#include "pch.h"
#include "CEntity.h"

UINT CEntity::g_NextID = 0;

CEntity::CEntity()
	: m_ID(g_NextID++)
{
}

CEntity::~CEntity()
{
}

CEntity::CEntity(const CEntity& _Other)
	: m_ID(g_NextID++)
	, m_strName(_Other.m_strName)
{
}
