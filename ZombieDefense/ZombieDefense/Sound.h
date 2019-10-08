#pragma once
#include "FMOD\include\fmod.hpp"
#pragma comment(lib,"FMOD/lib/fmod64_vc.lib")

using namespace FMOD;

class CSound
{
	System* m_pSystem;
	Sound* m_pSounds[SOUND_NUM];
	Channel* m_pChannel[SOUND_NUM];
public:
	CSound();
	virtual ~CSound();

	void Init();
	void Release();
	void Set_sound();
	void Play(size_t soundid);
};

