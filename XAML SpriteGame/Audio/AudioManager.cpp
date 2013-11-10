#include "pch.h"
#include "AudioManager.h"

using namespace Coding4Fun::FallFury::Audio;
 
Audio				AudioManager::AudioEngineInstance;
bool				AudioManager::IsMusicStarted;
bool				AudioManager::IsSFXStarted;

int					AudioManager::MusicVolume;
int					AudioManager::SFXVolume;

void AudioManager::Initialize()
{
	MusicVolume = 100;
	SFXVolume = 100;
	AudioEngineInstance.Initialize();
}

void AudioManager::Update()
{
	AudioEngineInstance.Render();
}

void AudioManager::SetGameOverMusic()
{ 
	AudioEngineInstance.~Audio();
	AudioEngineInstance.Initialize();
	AudioEngineInstance.ReInitializeStreamer(L"Assets\\Music\\game_over.wma");

	SetVolume();
	AudioEngineInstance.Start();

	CheckStates();
}

void AudioManager::SetMainMenuMusic()
{ 
	AudioEngineInstance.~Audio();
	AudioEngineInstance.Initialize();

	AudioEngineInstance.ReInitializeStreamer(L"Assets\\Music\\maintheme.wma");

	SetVolume();
	AudioEngineInstance.Start();

	CheckStates();
}

 

void AudioManager::SetGamePlayMusic()
{

	AudioEngineInstance.~Audio();
	AudioEngineInstance.Initialize();

	AudioManager::AudioEngineInstance.ReInitializeStreamer(L"maintheme.wma");
	 

	 
	AudioManager::AudioEngineInstance.Start();
	AudioEngineInstance.StartMusic();
 }

void AudioManager::CheckStates()
{
	if (IsMusicStarted)
		AudioEngineInstance.StartMusic();
	else
		AudioEngineInstance.SuspendMusic();

	if (IsSFXStarted)
		AudioEngineInstance.StartSFX();
	else
		AudioEngineInstance.SuspendSFX();
}

void AudioManager::SetMusicVolume(int percent)
{
	MusicVolume = percent;
	AudioEngineInstance.SetMusicVolume((percent / 100.f) * 1.0f);
}

void AudioManager::SetSFXVolume(int percent)
{
	SFXVolume = percent;
	AudioEngineInstance.SetAllSoundEffectVolume((percent / 100.f) * 1.0f);
}

void AudioManager::SetVolume()
{
	SetMusicVolume(MusicVolume);
	SetSFXVolume(SFXVolume);
}