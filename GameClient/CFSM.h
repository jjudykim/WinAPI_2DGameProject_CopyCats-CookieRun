#pragma once
#include "CComponent.h"

enum class DATA_TYPE
{
    INT,
    FLOAT,
    VEC2D,
    WSTRING,
    OBJECT,
    COOKIEINFO,
    ANIMATION,
};

struct BlackboardData
{
    DATA_TYPE   Type;
    void*       pData;
};

class CState;

class CFSM :
    public CComponent
{
private:
    static map<wstring, BlackboardData>         m_mapGlobalData;

private:
    map<wstring, BlackboardData>                m_mapData;
    map<wstring, CState*>                       m_mapState;
    CState*                                     m_CurState;

public:
    void AddState(const wstring& _strStateName, CState* _State);
    CState* FindState(const wstring& _strStateName);
    void ChangeState(const wstring& _strNextStateName);
    void SetBlackboardData(const wstring& _DataKey, DATA_TYPE _Type, void* _pData);
    void SetGlobalData(const wstring& _DataKey, DATA_TYPE _Type, void* _pData);

    template<typename T>
    T GetBlackboardData(const wstring& _DataKey);

    template<typename T>
    T GetGlobalData(const wstring& _DataKey);

public:
    virtual void finaltick() override;

public:
    CLONE(CFSM);

    CFSM();
    ~CFSM();
};

template<typename T>
inline T CFSM::GetBlackboardData(const wstring& _DataKey)
{
    map<wstring, BlackboardData>::iterator iter = m_mapData.find(_DataKey);

    assert(iter != m_mapData.end());

    if (std::is_same_v<int, T>)
    {
        assert(DATA_TYPE::INT == iter->second.Type);
        return *((T*)iter->second.pData);
    }

    if (std::is_same_v<float, T>)
    {
        assert(DATA_TYPE::FLOAT == iter->second.Type);
        return *((T*)iter->second.pData);
    }

    if (std::is_same_v<Vec2D, T>)
    {
        assert(DATA_TYPE::VEC2D == iter->second.Type);
        return *((T*)iter->second.pData);
    }

    if (std::is_same_v<CookieInfo, T>)
    {
        assert(DATA_TYPE::COOKIEINFO == iter->second.Type);
        return *((T*)iter->second.pData);
    }

    if constexpr (std::is_same_v<CObject*, T>)
    {
        assert(DATA_TYPE::OBJECT == iter->second.Type);
        return (T)iter->second.pData;
    }
}

template<typename T>
inline T CFSM::GetGlobalData(const wstring& _DataKey)
{
    map<wstring, BlackboardData>::iterator iter = m_mapGlobalData.find(_DataKey);

    assert(iter != m_mapGlobalData.end());

    if (std::is_same_v<int, T>)
    {
        assert(DATA_TYPE::INT == iter->second.Type);
        return *((T*)iter->second.pData);
    }

    if (std::is_same_v<float, T>)
    {
        assert(DATA_TYPE::FLOAT == iter->second.Type);
        return *((T*)iter->second.pData);
    }

    if (std::is_same_v<Vec2D, T>)
    {
        assert(DATA_TYPE::VEC2D == iter->second.Type);
        return *((T*)iter->second.pData);
    }

    if (std::is_same_v<CookieInfo, T>)
    {
        assert(DATA_TYPE::COOKIEINFO == iter->second.Type);
        return *((T*)iter->second.pData);
    }

    if constexpr (std::is_same_v<CObject*, T>)
    {
        assert(DATA_TYPE::OBJECT == iter->second.Type);
        return (T)iter->second.pData;
    }
}

