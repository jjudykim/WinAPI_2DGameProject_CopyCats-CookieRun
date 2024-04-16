#pragma once
class CGameDataMgr
{
	SINGLE(CGameDataMgr);

private:
	UINT m_HighGameScore;
	UINT m_CurGameScore;

	UINT m_GlobalGameCoin;
	UINT m_CurGameCoin;

	UINT m_MaxHP;
	UINT m_CurHP;

	bool m_CookieDead;

public:
	void init();
	void tick();

public:
	void AddScore(int _score) { m_CurGameScore += _score; }
	void AddCoin(int _coin) { m_CurGameCoin += _coin; }
	void AddHP(int _hp)
	{ 
		m_CurHP += _hp; 
		if (m_MaxHP < m_CurHP) { m_CurHP = m_MaxHP; }
	}
	void DeductHP(int _hp)
	{ 
		m_CurHP -= _hp;
		if (m_CurHP < 0) m_CookieDead = true;
	}
};

