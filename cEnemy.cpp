#include "DXUT.h"
#include "cEnemy.h"

cEnemy::cEnemy()
{
	m_hp = 0.f;
	m_atk = 0.f;
	m_divDelta = 2;

	m_bulletTime = 0.f;
	m_bulletDelay = 0.f;

	m_dirRot = 0.f;
	m_accelCurve = 0.f;
}

bool cEnemy::CanFire()
{
	RECT world = {
		GX(0),
		GY(0),
		GX(GAMESIZEX),
		GY(GAMESIZEY)
	};
	return AABB(GetObjCollider(), world);
}
