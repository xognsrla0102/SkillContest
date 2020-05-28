#include "DXUT.h"
#include "cBullet.h"
#include "cBulletManager.h"

cBulletManager::cBulletManager()
{
}

cBulletManager::~cBulletManager()
{
	Reset();
}

void cBulletManager::Update()
{
	for (auto iter : m_pBullet)
		iter->Update();
	for (auto iter : m_eBullet)
		iter->Update();
}

void cBulletManager::Render()
{
	for (auto iter : m_pBullet)
		iter->Render();
	for (auto iter : m_eBullet)
		iter->Render();
}

void cBulletManager::Reset()
{
	for (auto iter : m_pBullet)
		SAFE_DELETE(iter);
	for (auto iter : m_eBullet)
		SAFE_DELETE(iter);
}

void cBulletManager::N_Way_Tan(const string& bulletName, const string& imageName, int n, int theta, VEC2 pos, VEC2 dir, float bulletSpd, bool isRandShot, bool isHoming, bool isAccel)
{
	float rot = D3DXToDegree(atan2(dir.y, dir.x));
	float newRot;
	
	int randShotX = 0, randShotY = 0;

	if (n % 2) newRot = rot + (n / 2) * theta;
	else newRot = rot + (n / 2) * theta - theta / 2;

	for (size_t i = 0; i < n; ++i) {
		if (isRandShot) {
			randShotX = rand() % 50;
			randShotY = rand() % 50;
			dir.x = cos(D3DXToRadian(newRot + randShotX));
			dir.y = sin(D3DXToRadian(newRot + randShotY));
		}
		else {
			dir.x = cos(D3DXToRadian(newRot));
			dir.y = sin(D3DXToRadian(newRot));
		}
		D3DXVec2Normalize(&dir, &dir);

		if (bulletName == "PlayerBullet")
			m_pBullet.push_back(new cBullet(imageName, pos, dir, D3DXToDegree(atan2(dir.y, dir.x)) + 90, bulletSpd, VEC2(1, 1), isHoming, isAccel));
		else if (bulletName == "EnemyBullet")
			m_eBullet.push_back(new cBullet(imageName, pos, dir, D3DXToDegree(atan2(dir.y, dir.x)) + 90, bulletSpd, VEC2(1, 1), isHoming, isAccel));
		newRot -= theta;
	}
}

void cBulletManager::N_Straight_Tan(const string& bulletName, const string& imageName, int n, int length, VEC2 pos, VEC2 dir, float bulletSpd, bool isAccel)
{
	float rot = D3DXToDegree(atan2(dir.y, dir.x));

	if (n % 2) pos.x -= n / 2 * length;
	else pos.x -= n / 2 * length - length / 2;

	for (size_t i = 0; i < n; ++i) {
		auto bullet = new cBullet(imageName, VEC2(pos.x + i * length, pos.y), dir, rot + 90, bulletSpd, VEC2(1, 1), false, isAccel);

		if (bulletName == "PlayerBullet")
			m_pBullet.push_back(bullet);
		else if (bulletName == "EnemyBullet")
			m_eBullet.push_back(bullet);
	}
}

