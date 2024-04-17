#pragma once
class CGameDataMgr
{
	SINGLE(CGameDataMgr);

private:
	UINT m_HighGameScore;
	UINT m_CurGameScore;

	UINT m_GlobalGameCoin;
	UINT m_CurGameCoin;

	int m_MaxHP;
	int m_CurHP;

	bool m_CookieDead;

public:
	void init();
	void tick();

public:
	UINT GetHighScore() { return m_HighGameScore; }
	UINT GetCurScore() { return m_CurGameScore; }
	UINT GetCurGameCoin() { return m_CurGameCoin; }
	int GetCurHP() { return m_CurHP; }
	int GetMaxHP() { return m_MaxHP; }
	float GetRateHP() { return (float)m_CurHP / (float)m_MaxHP * 100.f; }
	bool IsCookieDead() { return m_CookieDead; }

	void SetMaxHP(int _hp) { m_MaxHP = _hp; }
	void SetGlobalGameCoin(int _hp) { m_GlobalGameCoin = _hp; }

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
		if (m_CurHP <= 0)
		{
			m_CurHP = 0;
			m_CookieDead = true;
		}
	}
};

