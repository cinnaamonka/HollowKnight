#include "base.h"
#include <iostream>
#include "SoundEffect.h"


SoundEffect::SoundEffect(const std::string& path)
	: m_pMixChunk{ Mix_LoadWAV(path.c_str()) }, m_channel(-1)
{
	if (m_pMixChunk == nullptr)
	{
		const std::string errorMsg = "SoundEffect: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError();
		std::cerr << errorMsg;
	}
}

SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(m_pMixChunk);
	m_pMixChunk = nullptr;
}

bool SoundEffect::IsLoaded() const
{
	return m_pMixChunk != nullptr;
}

bool SoundEffect::Play(const int loops)
{
	if (m_pMixChunk != nullptr)
	{
		
		if (m_channel != -1) return false;

		m_channel = Mix_PlayChannel(-1, m_pMixChunk, loops);

		return m_channel == -1 ? false : true;
	}
	else
	{
		return false;
	}
}

void SoundEffect::Stop()
{
	if (m_channel != -1)
	{
		Mix_HaltChannel(m_channel);
		m_channel = -1;
	}
}

void SoundEffect::SetVolume(const int value)
{
	if (m_pMixChunk != nullptr)
	{
		Mix_VolumeChunk(m_pMixChunk, value);
	}
}

int SoundEffect::GetVolume() const
{
	if (m_pMixChunk != nullptr)
	{
		return Mix_VolumeChunk(m_pMixChunk, -1);
	}
	else
	{
		return -1;
	}
}

void SoundEffect::StopAll()
{
	Mix_HaltChannel(-1);
}

void SoundEffect::PauseAll()
{
	Mix_Pause(-1);
}

void SoundEffect::ResumeAll()
{
	Mix_Resume(-1);
}




