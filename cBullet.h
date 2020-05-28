#pragma once
#include "cObject.h"
class cBullet : public cObject
{
private:
	float m_accel = 1.f;
	float m_bulletSpd;
public:
	VEC2 m_dir;
	float m_waveSpd = 0.f;
	bool m_isAccel;
	bool m_isHoming = false;
public:
	cBullet(const string& imageName, VEC2 pos, VEC2 dir, float rot, float bulletSpd = 300.f, VEC2 size = VEC2(1, 1), bool isHoming = false, bool isAccel = false);
	virtual ~cBullet();

	virtual void Update() override;
	virtual void Render() override;

	void Straight();
	void Homing();
};

