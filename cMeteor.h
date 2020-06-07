#pragma once
#include "cEnemy.h"
class cMeteor : public cEnemy
{
private:
	float m_downSpd;
public:
	cMeteor(string name, VEC2 pos, VEC2 size, float rot, float m_downSpd);
	virtual ~cMeteor();

	virtual void Update() override;
	virtual void Render() override;
};

