#pragma once
#include "cSingleton.hpp"

class cGameManager : public cSingleton<cGameManager>
{
public:
	float OLD_TIME_SCALE = 1.f;
	float TIME_SCALE = 1.f;
	int m_level = 1;
	bool m_isPause = false;
public:
	cGameManager();
	virtual ~cGameManager();

	void Update();
};

#define GAME cGameManager::GetInst()