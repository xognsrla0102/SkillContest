#pragma once
#include "cEnemy.h"
class cStraight : public cEnemy
{
private:
	float m_downSpd;
public:
	cStraight(VEC2 pos);
	virtual ~cStraight();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Dead() override;
	void Fire();
};

