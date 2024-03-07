#pragma once
#include "CComponent.h"

enum class DATA_TYPE
{
    INT,
    FLOAT,
    VEC2D,
    OBEJCT,
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

    template<typename T>
    T& GetBlackboardData(const wstring& _DataKey);

public:
    virtual void finaltick() override;

public:
    CLONE(CFSM);

    CFSM();
    ~CFSM();
};

