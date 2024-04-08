#pragma once
#include "CLevel.h"

#include "CAnimation.h"

class CTexture;
class CStage;
class CAnimation;
class CDraw;

class CLevel_Editor :
    public CLevel
{
private:
    HMENU       m_hMenu;
    int         m_EditMode;

    // Animation Editor
    CTexture*       m_EditTex;
    CAnimation*     m_EditAnim;
    AniFrm          m_CurFrm;

    CDraw*          m_CurDraw;
    CDraw*          m_PrevDraw;
    
    bool            m_PlayingAnim;
    bool            m_CreatingAnim;
    bool            m_Drawable;
    bool            m_Drawing;

    // Stage Editor
    CObject*        m_CurEditObject;
    CStage*         m_CurEditStage;
    CDraw*          m_GuideDraw;

    bool            m_Assigning;
    bool            m_Editing;
    bool            m_Deleting;
    bool            m_Dragging;
    bool            m_BGSetted;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void finaltick() override;
    virtual void render() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    vector<wstring> GetLoadedTextureKey();
    void SetObjectMouseCheck(bool _set);
    
    

    // Animation Editor
    void ResetAllAnimationOption();

    void SetEditMode(int _mode) { m_EditMode = _mode; }
    void SetEditTex(CTexture* _tex) { m_EditTex = _tex; }
    void SetEditAnim(CAnimation* _anim) { m_EditAnim = _anim; }
    void SetCurFrm(const AniFrm& _frm) { m_CurFrm = _frm; }
    void SetDrawable(bool _drawable) { m_Drawable = _drawable; }
    void SetDrawing(bool _drawing) { m_Drawing = _drawing; }
    void SetCreatingAnimState(bool _State) { m_CreatingAnim = _State; }
    void SetPlayingAnimState(bool _State) { m_PlayingAnim = _State; }

    CTexture* GetEditTex() { return m_EditTex; }
    CAnimation* GetEditAnim() { return m_EditAnim; }
    const AniFrm& GetCurFrm() { return m_CurFrm; }
    bool GetDrawable() { return m_Drawable; }
    CDraw* GetPrevDraw() { return m_PrevDraw; }
    bool GetDrawing() { return m_Drawing; }
    bool GetCreatingAnimState() { return m_CreatingAnim; }
    bool GetPlayingAnimState() { return m_PlayingAnim; }


    // Stage Editor
    void SetAssigning(bool _assigning) { m_Assigning = _assigning; }
    void SetEditing(bool _editing) { m_Editing = _editing; }
    void SetDeleting(bool _deleting) { m_Deleting = _deleting; }
    void SetEditStage(CStage* _stage) { m_CurEditStage = _stage; }
    void SetBGSetted(bool _setted) { m_BGSetted = _setted; }

    bool GetAssigning() { return m_Assigning; }
    bool GetEditing() { return m_Editing; }
    bool GetDeleting() { return m_Deleting; }
    CObject* GetEditObject() { return m_CurEditObject; }
    CStage* GetEditStage() { return m_CurEditStage; }
    int GetEditMode() { return m_EditMode; }
    bool GetBGSetted() { return m_BGSetted; }
   
    void ResetForLoadStage();
    //void AddAnimFrm(AniFrm _frm) { m_vecFrm.push_back(_frm); }
    //const int& GetAnimFrmCount() { return m_vecFrm.size(); }

    AniFrm GetAnimFrm(int _index) { return m_EditAnim->GetFrame(_index); }

public:
    CLONE_DISABLE(CLevel_Editor);
    CLevel_Editor();
    ~CLevel_Editor();

    friend class CDraw;
};

