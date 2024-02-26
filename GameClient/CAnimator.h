#pragma once
#include "CComponent.h"
class CAnimator :
    public CComponent
{

private:
    map<wstring, CAnimation*> m_mapAnim;
};

