#pragma once
#include "cEnemy.h"
class cRazer : public cEnemy
{
private:
	cAnimation* m_chargeEffect;
	bool m_isChargeTime = false;
public:
	cRazer(VEC2 pos);
	virtual ~cRazer();

	virtual void Update() override;
	virtual void Render() override;
	void Fire();
};

