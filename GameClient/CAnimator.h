#pragma once
#include "CComponent.h"

class CAnimation;

class CAnimator :
    public CComponent
{

private:
    map<wstring, CAnimation*> m_mapAnim;
};

