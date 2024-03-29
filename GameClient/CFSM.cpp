#include "pch.h"
#include "CFSM.h"

#include "CState.h"

map<wstring, BlackboardData> CFSM::m_mapGlobalData;

CFSM::CFSM()
{
	
}

CFSM::~CFSM()
{
}

void CFSM::finaltick()
{
	if (m_CurState == nullptr)
		return;

	m_CurState->FinalTick();
}

void CFSM::AddState(const wstring& _strStateName, CState* _State)
{
	assert(!FindState(_strStateName));

	_State->m_Owner = this;
	m_mapState.insert(make_pair(_strStateName, _State));
}

void CFSM::SetState()
{
	for (const auto& pair : m_mapState)
	{
		pair.second->Set();
	}
}

CState* CFSM::FindState(const wstring& _strStateName)
{
	map<wstring, CState*>::iterator iter = m_mapState.find(_strStateName);

	if (iter == m_mapState.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CFSM::ChangeState(const wstring& _strNextStateName)
{
	if (m_CurState && (_strNextStateName == m_CurState->GetName()))
		return;

	if (m_CurState != nullptr)
		m_CurState->Exit();

	m_CurState = FindState(_strNextStateName);
	assert(m_CurState);

	m_CurState->Enter();
}

void CFSM::SetBlackboardData(const wstring& _DataKey, DATA_TYPE _Type, void* _pData)
{
	BlackboardData data = { _Type, _pData };
	m_mapData.insert(make_pair(_DataKey, data));
}

void CFSM::SetGlobalData(const wstring& _DataKey, DATA_TYPE _Type, void* _pData)
{
	BlackboardData data = { _Type, _pData };
	m_mapGlobalData.insert(make_pair(_DataKey, data));
}
