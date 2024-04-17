#pragma once
#include "CLevel.h"

class CStage;
class CPlayer;
class CPet;
class CSound;

class CLevel_Game :
    public CLevel
{
private:
    CStage*     m_PrevStage;
    CStage*     m_CurStage;
    CStage*     m_PostStage;
    
    float       m_ResolutionWidth;
    float       m_ActingPosX;
    float       m_DeletePosX;
    float       m_PostStageStartPosX;

    CSound*     m_BGM;
    CPlayer*    m_Cookie;
    CPet*       m_Pet;

    bool        m_GameOver;

    // Timer & Log
    int         m_CookieStateAction;
    Vec2D       m_LogPos;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

    

public:
    void LoadSoundResource();
    void SpawnStageSTObject(StageSTObjInfo& _ObjInfo);
    void SpawnStageDNObject(StageDNObjInfo& _ObjInfo);
    void PrintCookieLog();
    //void DeleteStageObject(CObject* _Obj);
public:
    CLONE_DISABLE(CLevel_Game);

public:
    CLevel_Game();
    ~CLevel_Game();

    friend class CLevelMgr;
};

