#pragma once
#include "cEnemy.h"
class cRotate : public cEnemy
{
public:
	cRotate(VEC2 pos);
	virtual ~cRotate();

	virtual void Update() override;
	virtual void Render() override;
	void Fire();
};

