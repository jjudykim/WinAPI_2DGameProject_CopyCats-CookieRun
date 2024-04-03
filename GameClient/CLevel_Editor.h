#pragma once
#include "CLevel.h"

#include "CAnimation.h"

class CTexture;
class CAnimation;
class CDraw;

class CLevel_Editor :
    public CLevel
{
private:
    HMENU       m_hMenu;
    
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

    bool            m_Editing;
    bool            m_Dragging;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void finaltick() override;
    virtual void render() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    vector<wstring> GetLoadedTextureKey();

    // Animation Editor
    void ResetAllAnimationOption();

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
    bool GetEditing() { return m_Editing; }
    void SetEditing(bool _editing) { m_Editing = _editing; }
    //void AddAnimFrm(AniFrm _frm) { m_vecFrm.push_back(_frm); }
    //const int& GetAnimFrmCount() { return m_vecFrm.size(); }
    AniFrm GetAnimFrm(int _index) { return m_EditAnim->GetFrame(_index); }

public:
    CLONE_DISABLE(CLevel_Editor);
    CLevel_Editor();
    ~CLevel_Editor();

    friend class CDraw;
};

