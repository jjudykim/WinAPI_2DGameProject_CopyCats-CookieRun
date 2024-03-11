#pragma once
#include "CEntity.h"

class CStage :
    public CEntity
{
    vector<CObject*>    m_arrObj[(UINT)LAYER_TYPE::END];
};

