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

	bool m_isPause;
	bool m_isNotDead;
	bool m_isDebugInfo;

	bool m_isMidBoss;
	bool m_isBoss;

	bool m_isF1;
public:
	cGameManager();
	virtual ~cGameManager();

	void StageInit();
	void Init();
	void Update();
};

#define GAME cGameManager::GetInst()