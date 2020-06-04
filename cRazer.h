#pragma once
#include "cEnemy.h"
class cRazer : public cEnemy
{
public:
	cRazer(VEC2 pos);
	virtual ~cRazer();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Dead() override;
};

