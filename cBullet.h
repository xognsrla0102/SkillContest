#pragma once
#include "cObject.h"
class cBullet : public cObject
{
private:
	float m_accel = 1.f;
	float m_bulletSpd;
public:
	string m_bulletName;
	VEC2 m_dir;
	bool m_isAccel;
	bool m_isHoming;
public:
	cBullet(const string& bulletName, VEC2 pos, float rot, float bulletSpd = 300.f, VEC2 size = VEC2(1, 1), bool isAccel = false);
	virtual ~cBullet();

	virtual void Update() override;
	virtual void Render() override;

	void Straight();
	void Homing();
};

