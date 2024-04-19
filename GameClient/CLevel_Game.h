#pragma once
#include "CLevel.h"

class CStage;
class CPlayer;
class CPet;
class CSound;
class CButtonUI;
class CImageUI;
class CPanelUI;

class CLevel_Game :
    public CLevel
{
private:
    CStage*     m_PrevStage;
    CStage*     m_CurStage;
    CStage*     m_PostStage;
    
    Vec2D       m_Resolution;
    float       m_ActingPosX;
    float       m_DeletePosX;
    float       m_PostStageStartPosX;
    float       m_DestinationPosX;

    CSound*     m_BGM;
    CPlayer*    m_Cookie;
    CPet*       m_Pet;

    CButtonUI*  m_BtnJump;
    CButtonUI*  m_BtnSlide;
    CImageUI*   m_MarkMiniMap;
    CImageUI*   m_HeartGauge;
    CImageUI*   m_HeartGaugeEffect;
    CImageUI*   m_BTAlphabet[9];

    CPanelUI*   m_CoinScoreUI;
    CPanelUI*   m_HighScoreUI;
    CPanelUI*   m_CurScoreUI;
    vector<int> m_vecScore;

    bool        m_GameOver;

    // Timer & Log
    bool        m_JellyAttract;
    int         m_CookieStateAction;
    Vec2D       m_LogPos;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

   
public:
    void SetHUD();
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

