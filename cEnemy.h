#pragma once
#include "cObject.h"
class cEnemy : public cObject 
{
protected:
	int m_hp;
public:
	cEnemy() {}
	virtual ~cEnemy() {}

	virtual void Update() PURE;
	virtual void Render() PURE;

	virtual void Dead() PURE;
};

