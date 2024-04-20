#pragma once

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	WHITE_FADE_IN,
	WHITE_FADE_OUT,
	DAMAGE_FADE_IN,
	DAMAGE_FADE_OUT,
	NONE,
};

struct CAM_EFFECT_INFO
{
	CAM_EFFECT		Effect;
	float			Duration;
	float			Time;
	float			Alpha;
};

class CTexture;
class CObject;

class CCamera
{
	SINGLE(CCamera)
private:
	CObject*		m_FocusObj;

	Vec2D			m_LookAt;
	Vec2D			m_PrevLookAt;
	Vec2D			m_Diff;
	float			m_CamSpeed;
	float			m_LimitPosX;

	list<CAM_EFFECT_INFO> m_EffectList;

	CTexture*		m_FadeTex;
	CTexture*		m_WhiteTex;
	CTexture*		m_DamageTex;


public:
	Vec2D GetRenderPos(Vec2D _RealPos) { return _RealPos - m_Diff; }
	Vec2D GetRealPos(Vec2D _RenderPos) { return _RenderPos + m_Diff; }
	Vec2D GetLookAt() { return m_LookAt; }
	void SetLimitPosX(float _PosX) { m_LimitPosX = _PosX; }
	void SetCameraDefault();
	void SetCameraFocus();
	void SetCameraEffect(CAM_EFFECT _Effect, float _Duration);

public:
	void init();
	void tick();
	void render();

private:
	void MoveAll();
	void MoveLR();
	void CameraEffect();
};

