#pragma once
#include "cEnemy.h"
class cRadial : public cEnemy
{
private:
	float m_downSpd;
public:
	cRadial(VEC2 pos);
	virtual ~cRadial();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Dead() override;
	void Fire();
};

