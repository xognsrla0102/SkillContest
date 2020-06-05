#pragma once
#include "cSingleton.hpp"

class cGameManager : public cSingleton<cGameManager>
{
public:
	float OLD_TIME_SCALE;
	float TIME_SCALE;

	int m_expMax;

	int m_nowExp;
	int m_totalExp;

	int m_level;

	int m_nowStage = 1;

	bool m_isPause;
public:
	cGameManager();
	virtual ~cGameManager();

	void Init();
	void Update();
};

#define GAME cGameManager::GetInst()