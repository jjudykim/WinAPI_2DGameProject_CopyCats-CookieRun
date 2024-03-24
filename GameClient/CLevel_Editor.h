#pragma once
#include "CLevel.h"

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
    CDraw*          m_CurDraw;
    CDraw*          m_PrevDraw;
    vector<AniFrm>  m_vecFrm;

    bool            m_CreatingAnim;
    bool            m_Drawable;
    bool            m_Drawing;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void render() override;

    virtual void Enter() override;
    virtual void Exit() override;

public:
    vector<wstring> GetLoadedTextureKey();
    
    // Animation Editor
    void SetEditTex(CTexture* _tex) { m_EditTex = _tex; }
    void SetEditAnim(CAnimation* _anim) { m_EditAnim = _anim; }
    void SetDrawable(bool _drawable) { m_Drawable = _drawable; }
    void SetDrawing(bool _drawing) { m_Drawing = _drawing; }
    void SetCreatingAnimState(bool _State) { m_CreatingAnim = _State; }

    CTexture* GetEditTex() { return m_EditTex; }
    CAnimation* GetEditAnim() { return m_EditAnim; }
    bool GetDrawable() { return m_Drawable; }
    CDraw* GetPrevDraw() { return m_PrevDraw; }
    bool GetDrawing() { return m_Drawing; }
    bool GetCreatingAnimState() { return m_CreatingAnim; }

    void AddAnimFrm(const AniFrm& _frm) { m_vecFrm.push_back(_frm); }
    const int& GetAnimFrmCount() { return m_vecFrm.size(); }
    AniFrm& GetAnimFrm(int _index) { return m_vecFrm[_index]; }
    void SetAnimFrm(int _index, const Vec2D& _StartPos, const Vec2D& _SliceSize, const Vec2D& _Offset)
    {
        m_vecFrm[_index].StartPos = _StartPos;
        m_vecFrm[_index].SliceSize = _SliceSize;
        m_vecFrm[_index].Offset = _Offset;
    }
    void DeleteAnimFrm(int _index)
    { 
        vector<AniFrm>::iterator iter = m_vecFrm.begin();
        iter += _index;
        m_vecFrm.erase(iter);
    }

public:
    CLONE_DISABLE(CLevel_Editor);
    CLevel_Editor();
    ~CLevel_Editor();

    friend class CDraw;
};

