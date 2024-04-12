#pragma once

class CSound;

class CSoundMgr
{
	SINGLE(CSoundMgr)

private:
	LPDIRECTSOUND8		m_pSound;
	CSound*				m_pBGM;

public:
	int init();
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
	void RegisterToBGM(CSound* _pSound);
};

