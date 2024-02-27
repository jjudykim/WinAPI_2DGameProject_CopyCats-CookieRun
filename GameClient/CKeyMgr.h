#pragma once

enum class KEY
{
	_0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,

	LEFT, RIGHT, UP, DOWN,

	ENTER,
	SPACE,
	ALT,
	CTRL,
	SHIFT,
	ESC,

	LBTN,
	RBTN,

	KEY_END,
};

enum class KEY_STATE
{
	TAP,
	PRESSED,
	RELEASED,
	NONE,
};

struct KeyInfo
{
	KEY			eKey;
	KEY_STATE	eKeyState;
	bool		bPressed;
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<KeyInfo>	m_vecKeyInfo;

public:
	void init();
	void tick();

public:
	KEY_STATE GetKeyState(KEY _Key) { return m_vecKeyInfo[(UINT)_Key].eKeyState; }
};


