#pragma once
#include "CAsset.h"
class CSound :
    public CAsset
{
private:
    LPDIRECTSOUNDBUFFER               m_pSoundBuffer;
    DSBUFFERDESC                      m_tBuffInfo;
    int                               m_iVolume;

public:
    virtual int Load(const wstring& _strFilePath);

private:
    bool LoadWaveSound(const wstring& _strPath);

public:
    void Play(bool _bLoop = false);
    void PlayToBGM(bool _bLoop = false);
    void Stop(bool _bReset = false);
    void SetVolume(float _fVolume);         // 0 ~ 100
    void SetPosition(float _fPosition);     // 0 ~ 100

    int GetDecibel(float _fVolume);
public:
    CLONE_DISABLE(CSound);

    CSound();
    ~CSound();


};

