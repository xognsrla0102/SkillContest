#pragma once
#include "cObject.h"
class cEnemy abstract : public cObject 
{
public:
	vector<string> m_itemNames;

	cPath* m_path = nullptr;

	int m_hp   = 0.f;
	int m_atk  = 0.f;
	int m_divDelta = 2;

	float m_bulletTime	= 0.f;
	float m_bulletDelay = 0.f;

	float m_dirRot		= 0.f;
	float m_accelCurve	= 0.f;

	bool m_isAccelCurve = false;
public:
	cEnemy();
	virtual ~cEnemy() {}

	virtual void Update() PURE;
	virtual void Render() PURE;

	virtual bool CanFire();

	vector<string>& GetItemNames() { return m_itemNames; }
};

