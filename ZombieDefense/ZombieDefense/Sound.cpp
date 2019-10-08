#include "stdafx.h"
#include "Sound.h"

CSound::CSound()
{
	CSound::Init();
	CSound::Set_sound();
}

CSound::~CSound()
{
	CSound::Release();
}

void CSound::Init()
{
	// 시스템을 크리에이트
	FMOD::System_Create(&m_pSystem);
	// 시스템을 Init
	m_pSystem->init(SOUND_NUM, FMOD_INIT_NORMAL, nullptr);
	// 사운드를 null상태로 초기화
	for (int i = 0; i < SOUND_NUM; ++i)
		m_pSounds[i] = nullptr;
}

void CSound::Release()
{
	// 사운드를 릴리즈
	for (int i = 0; i < SOUND_NUM; ++i)
		m_pSounds[i]->release();

	// 시스템 릴리즈
	m_pSystem->release();

	// 시스템 닫기
	m_pSystem->close();
}

void CSound::Set_sound()
{
	// BGM
	// Logo
	m_pSystem->createStream("../Sound/LogoBgm.mp3", FMOD_2D | FMOD_LOOP_NORMAL	//FMOD_LOOP_NORMAL 반복적인 노래
		,nullptr
		, &m_pSounds[BGM1]	// 몇번째 노래를 틀을까?
	);	
	// Game
	m_pSystem->createStream("../Sound/GameBgm.mp3", FMOD_2D | FMOD_LOOP_NORMAL, nullptr, &m_pSounds[BGM2]);
	m_pSystem->createStream("../Sound/skyway.mp3", FMOD_2D | FMOD_LOOP_NORMAL, nullptr, &m_pSounds[BGM3]);

	

	// 버튼
	m_pSystem->createStream("../Sound/UI_button2.wav", FMOD_DEFAULT | FMOD_LOOP_OFF	, nullptr, &m_pSounds[BUTTON1]);
	m_pSystem->createStream("../Sound/UI_button.wav", FMOD_DEFAULT | FMOD_LOOP_OFF	, nullptr, &m_pSounds[BUTTON2]);
	m_pSystem->createStream("../Sound/button3.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, nullptr, &m_pSounds[BUTTON3]);

	// 식물 심기
	m_pSystem->createStream("../Sound/Sound01.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, nullptr, &m_pSounds[EFFECT1]);
	m_pSystem->createStream("../Sound/Sound02.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, nullptr, &m_pSounds[EFFECT2]);
	m_pSystem->createStream("../Sound/Sound03.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, nullptr, &m_pSounds[EFFECT3]);
	m_pSystem->createStream("../Sound/Sound04.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, nullptr, &m_pSounds[EFFECT4]);
	m_pSystem->createStream("../Sound/explosion_01.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, nullptr, &m_pSounds[EFFECT5]);
	m_pSystem->createStream("../Sound/charge_tune.wav", FMOD_DEFAULT | FMOD_LOOP_OFF, nullptr, &m_pSounds[EFFECT6]);
}

void CSound::Play(size_t soundid)
{
	// 업데이트를 해주지 않으면 에러가 날수있다.
	m_pSystem->update();

	m_pSystem->playSound(m_pSounds[soundid], nullptr, false, &m_pChannel[soundid]);
}
