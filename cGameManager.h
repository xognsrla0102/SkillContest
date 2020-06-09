#pragma once
#include "cSingleton.hpp"

class cScore {
public:
	string m_initial;
	int m_score;
public:
	cScore() {}
	cScore(string initial, int score) : m_initial(initial), m_score(score) {}
};

class cGameManager : public cSingleton<cGameManager>
{
public:
	cScore* m_scoreList[4];

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
	void SortScore();
};

#define GAME cGameManager::GetInst()