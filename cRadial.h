#pragma once
#include "cEnemy.h"
class cRadial : public cEnemy
{
private:
	float m_downSpd;
	int dir = 1;
public:
	cRadial(VEC2 pos);
	virtual ~cRadial();

	virtual void Update() override;
	virtual void Render() override;
	void Fire();
};

