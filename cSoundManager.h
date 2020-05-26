#pragma once
#include "cSingleton.hpp"

class cSoundManager : public cSingleton<cSoundManager>
{
private:
	map<string, CSound*> m_sounds;
	CSoundManager* m_manager;
public:
	cSoundManager();
	virtual ~cSoundManager();

	void AddSound(string str, wstring path);
	void Play(string str, BOOL isLoop);
	void Copy(string str);
	void Stop(string str);
};

#define SOUND cSoundManager::GetInst()