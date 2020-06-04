#pragma once
#include "cSingleton.hpp"

class cGameManager : public cSingleton<cGameManager>
{
public:
	float OLD_TIME_SCALE = 1.f;
	float TIME_SCALE = 1.f;

	int m_expMax = 1000;

	int m_nowExp = 0;
	int m_totalExp = 0;

	int m_level = 1;

	int m_nowStage = 0;

	bool m_isPause = false;
public:
	cGameManager();
	virtual ~cGameManager();

	void Init();
	void Update();
};

#define GAME cGameManager::GetInst()