#pragma once
#include "cObject.h"
class cBullet : public cObject
{
private:
	float m_accel;
	float m_bulletSpd;
public:
	VEC2 m_dir;
	bool m_isFaccel = false;
	bool m_isSaccel = false;
	bool m_isHoming;
public:
	cBullet(const string& imageName, VEC2 pos, VEC2 dir, float rot, float bulletSpd, VEC2 size = VEC2(1, 1), bool isHoming = false, bool isFAccel = false, bool isSAccel = false);
	virtual ~cBullet();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnCollision(cObject* other);

	void Dead();
	void Homing();
};

