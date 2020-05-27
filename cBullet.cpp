#include "DXUT.h"
#include "cBullet.h"

cBullet::cBullet(const string& bulletName, VEC2 pos, float rot, float bulletSpd, VEC2 size, bool isAccel)
	: m_bulletName(bulletName), m_bulletSpd(bulletSpd), m_isAccel(isAccel)
{
	m_pos = pos;
	m_rot = rot;
	m_size = size;
}

cBullet::~cBullet()
{
}

void cBullet::Update()
{
	if (m_isHoming) Homing();
}

void cBullet::Render()
{
}

void cBullet::Straight()
{
}

void cBullet::Homing()
{
}
