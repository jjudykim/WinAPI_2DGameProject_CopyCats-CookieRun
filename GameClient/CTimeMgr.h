#pragma once

struct Timer
{
	float duration;
	float currentTime;
	std::function<void()> callback;
	bool repeat;
};

class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	static float AccTime;
	static wchar_t szBuff[255];

	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	UINT  m_FPS;
	float m_DeltaTime;
	float m_Time;

	vector<Timer> m_VecTimers;

public:
	void init();
	void tick();
	void render();

public:
	float GetDeltaTime() { return m_DeltaTime; }
	float GetTime() { return m_Time; }
	UINT GetFPS() { return m_FPS; }

public:
	void TimerUpdate();
	void AddTimer(float duration, std::function<void()> callback, bool repeat = false)
	{ 
		m_VecTimers.push_back({duration, 0.0f, callback, repeat});
	}
};

