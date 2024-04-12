#pragma once
#include "CLevel.h"

class CStage;
class CPlayer;
class CPet;
class CTexture;
class CSound;

class CLevel_Game :
    public CLevel
{
private:
    CStage*     m_CurStage;
    CStage*     m_PostStage;
    
    float       m_ResolutionWidth;
    float       m_ActingPosX;
    float       m_DeletePosX;
    float       m_PostStageStartPosX;

    CPlayer*    m_Cookie;
    CPet*       m_Pet;

    CTexture*   m_LoadingTex;
    CSound*     m_BGM;

    // Timer & Log
    float       m_Second;
    float       m_QuaterSecond;
    float       m_ThreeSecond;
    Vec2D       m_LogPos;
    Vec2D       m_LogPetPos;

    bool        m_LoadDone;
    bool        m_LevelBegin;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void finaltick() override;
    virtual void render() override;

    virtual void Enter() override;
    virtual void Exit() override;


public:
    int LoadGameData();
    void SpawnStageSTObject(StageSTObjInfo& _ObjInfo);
    void SpawnStageDNObject(StageDNObjInfo& _ObjInfo);

    void SetLoadDone(bool _Load) { m_LoadDone = _Load; }
    
    //void DeleteStageObject(CObject* _Obj);
public:
    CLONE_DISABLE(CLevel_Game);

public:
    CLevel_Game();
    ~CLevel_Game();

    friend class CLevelMgr;
};

