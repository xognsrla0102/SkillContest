#pragma once
#include "cEnemy.h"
class cMidBoss : public cEnemy
{
private:
	cTimer* m_timePlus;
	VEC2 m_nextPos;
	bool m_isMoveDone = true;
	float m_circleTan = 0.f;
	float m_straightTan = 0.f;
	int m_dirRot = 0;
public:
	int m_patternTime = 0;
public:
	cMidBoss();
	virtual ~cMidBoss();

	virtual void Update() override;
	virtual void Render() override;
};

