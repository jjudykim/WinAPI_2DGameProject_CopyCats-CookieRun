#pragma once
#include "CLevel.h"

class CStage;

class CLevel_Game :
    public CLevel
{
private:
    CStage*     m_CurStage;
    CStage*     m_PostStage;
    
    float       m_ResolutionWidth;
    float       m_SpawnPosX;
    float       m_DeletePosX;

    CObject*    m_Cookie;
    float       m_QuaterSecond;
    Vec2D       m_LogPos;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void Enter() override;
    virtual void Exit() override;

    

public:
    void SpawnStageObject(StageObjInfo& _ObjInfo);
    //void DeleteStageObject(CObject* _Obj);
    void LoadFromFile(const wstring& _FullPath);
public:
    CLONE_DISABLE(CLevel_Game);

public:
    CLevel_Game();
    ~CLevel_Game();
};

