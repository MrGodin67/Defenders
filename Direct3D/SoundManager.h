#pragma once
#include "SoundEffect.h"
#include "includes.h"
class SoundManager
{
	std::unordered_map<std::string, SoundEffect> m_soundFX;
	std::vector<SoundEffect*> m_soundFXQueue;
	float pl = 0.0f;;
	float volume = 1.0f;
public:
	SoundManager() {}
	~SoundManager() {}
	void AddToQueue(std::string name)
	{
		// if empty add and start playing
		if (m_soundFXQueue.size() == 0)
			m_soundFX[name].Play(pl,volume);

		m_soundFXQueue.push_back(&m_soundFX[name]);
	}
	bool PlayQueue()
	{
		if (m_soundFXQueue.size() == 0u)
			return false;

		if (m_soundFXQueue[0]->IsPlaying(0))
		{
			return true;
		}
		else
		{
			m_soundFXQueue.erase(m_soundFXQueue.begin());
			if (m_soundFXQueue.size() > 0u)
			{
				m_soundFXQueue[0]->Play(pl,volume);
				return true;
			}
			
		}
		return false;
	}
	void AddSound(std::string name, std::wstring file)
	{
		m_soundFX[name] = SoundEffect({ file.c_str() });
	}
	void Play(std::string sound,float in_volume)
	{
		m_soundFX[sound].Play(pl,in_volume);
	}
	void Play(std::string sound)
	{
		m_soundFX[sound].Play(pl,volume);
	}
	void SetVolume(float vol) { volume = vol; }
};