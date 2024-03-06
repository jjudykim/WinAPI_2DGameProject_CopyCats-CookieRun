#pragma once

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
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

class CCamera
{
	SINGLE(CCamera)
private:
	Vec2D			m_LookAt;
	Vec2D			m_Diff;
	float			m_CamSpeed;
	float			m_Time;
	list<CAM_EFFECT_INFO> m_EffectList;

	CTexture*		m_FadeTex;

public:
	Vec2D GetRenderPos(Vec2D _RealPos) { return _RealPos - m_Diff; }
	Vec2D GetRealPos(Vec2D _RenderPos) { return _RenderPos + m_Diff; }

	void SetCameraEffect(CAM_EFFECT _Effect, float _Duration);

public:
	void init();
	void tick();
	void render();

private:
	void Move();
	void CameraEffect();
};

