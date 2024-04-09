#pragma once
#include "CLevel.h"

class CStage;
class CPlayer;
class CPet;

class CLevel_Game :
    public CLevel
{
private:
    CStage*     m_CurStage;
    CStage*     m_PostStage;
    
    float       m_ResolutionWidth;
    float       m_SpawnPosX;
    float       m_DeletePosX;

    CPlayer*    m_Cookie;
    CPet*       m_Pet;


    // Timer & Log
    float       m_QuaterSecond;
    float       m_ThreeSecond;
    Vec2D       m_LogPos;
    Vec2D       m_LogPetPos;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

    

public:
    void SpawnStageObject(StageSTObjInfo& _ObjInfo);
    //void DeleteStageObject(CObject* _Obj);
public:
    CLONE_DISABLE(CLevel_Game);

public:
    CLevel_Game();
    ~CLevel_Game();
};

