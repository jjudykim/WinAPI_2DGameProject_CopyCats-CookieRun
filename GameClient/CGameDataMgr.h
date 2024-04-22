#pragma once
class CGameDataMgr
{
	SINGLE(CGameDataMgr);

private:
	UINT	m_HighGameScore;
	UINT	m_CurGameScore;
	bool	m_ScoreEditing;

	UINT	m_GlobalGameCoin;
	UINT	m_CurGameCoin;
	bool	m_CoinEditing;

	wstring	m_CurPlayCookie;
	wstring	m_CurPlayPet;
	
	int		m_MaxHP;
	int		m_CurHP;

	bool	m_BonusTime[9];
	bool	m_BTEditing;

	bool	m_CookieDead;

public:
	void init();
	void tick();
	void LoadFromFile();
	void SaveToFile();
	
public:
	UINT GetHighScore() { return m_HighGameScore; }
	UINT GetCurScore() { return m_CurGameScore; }
	UINT GetGlobalGameCoin() { return m_GlobalGameCoin; }
	UINT GetCurGameCoin() { return m_CurGameCoin; }
	wstring GetCurPlayCookie() { return m_CurPlayCookie; }
	wstring GetCurPlayPet() { return m_CurPlayPet; }
	int GetCurHP() { return m_CurHP; }
	int GetMaxHP() { return m_MaxHP; }
	float GetRateHP() { return (float)m_CurHP / (float)m_MaxHP * 100.f; }
	bool IsScoreEditing() { return m_ScoreEditing; }
	bool IsCoinEditing() { return m_CoinEditing; }
	bool IsBTEditing() { return m_BTEditing; }
	bool IsCookieDead() { return m_CookieDead; }
	bool CheckAlphabetOn(int _index) { return m_BonusTime[_index]; }

	void ResetForGame();
	
	void SetMaxHP(int _hp) { m_MaxHP = _hp; }
	void SetGlobalGameCoin(int _hp) { m_GlobalGameCoin = _hp; }
	void SetCurPlayCookie(wstring _Cookie) { m_CurPlayCookie = _Cookie; }
	void SetCurPlayPet(wstring _Pet) { m_CurPlayPet = _Pet; }
	void DoneCoinEditing() { m_CoinEditing = false; }
	void DoneScoreEditing() { m_ScoreEditing = false; }
	void DoneBTEditing() { m_BTEditing = false; }
	
	void AddScore(int _score)
	{ 
		m_CurGameScore += _score; 
		m_ScoreEditing = true;
	}

	void AddCoin(int _coin) 
	{ 
		m_CurGameCoin += _coin; 
		m_CoinEditing = true;
	}

	void AddBonusTimeAlphabet(int _index) 
	{ 
		m_BonusTime[_index] = true; 
		m_BTEditing = true;
	}

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

