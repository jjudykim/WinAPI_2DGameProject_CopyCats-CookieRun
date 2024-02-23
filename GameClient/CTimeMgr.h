#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	static float AccTime;
	static wchar_t szBuff[255];

	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	UINT m_FPS;
	float m_DeltaTime;
	float m_Time;

public:
	void init();
	void tick();
	void render();

public:
	float GetDeltaTime() { return m_DeltaTime; }
	float GetTime() { return m_Time; }
	UINT GetFPS() { return m_FPS; }
};

