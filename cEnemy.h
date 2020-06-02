#pragma once
#include "cObject.h"
class cEnemy : public cObject 
{
public:
	int m_hp;
	int m_atk;
public:
	cEnemy() {}
	virtual ~cEnemy() {}

	virtual void Update() PURE;
	virtual void Render() PURE;

	virtual void Dead() PURE;
	virtual void OnCollision(cObject* other) PURE;
};

