#pragma once
#include "cSingleton.hpp"

class cGameManager : public cSingleton<cGameManager>
{
public:
	float OLD_TIME_SCALE;
	float TIME_SCALE;

	int m_expMax;

	int m_nowExp;
	int m_score;

	int m_level;

	int m_nowStage = 1;

	int m_learnBullet1;
	int m_learnBullet2;
	int m_learnBullet3;

	bool m_isPause;
	bool m_isNotDead;
	bool m_isDebugInfo;
public:
	cGameManager();
	virtual ~cGameManager();

	void Init();
	void Update();
};

#define GAME cGameManager::GetInst()