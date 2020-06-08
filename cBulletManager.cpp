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
	size_t size = m_pBullet.size();
	for (size_t i = 0; i < size; ++i) {
		m_pBullet[i]->Update();
		if (m_pBullet[i]->GetLive() == FALSE) {
			SAFE_DELETE(m_pBullet[i]);
			m_pBullet.erase(m_pBullet.begin() + i);
			i--, size--;
		}
	}

	size = m_eBullet.size();
	for (size_t i = 0; i < size; ++i) {
		m_eBullet[i]->Update();
		if (m_eBullet[i]->GetLive() == FALSE) {
			SAFE_DELETE(m_eBullet[i]);
			m_eBullet.erase(m_eBullet.begin() + i);
			i--, size--;
		}
	}
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
	m_pBullet.clear();
	for (auto iter : m_eBullet)
		SAFE_DELETE(iter);
	m_eBullet.clear();
}

void cBulletManager::N_Way_Tan(const string& bulletName, const string& imageName, int n, int theta, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isRandShot, bool isHoming, bool isFaccel, bool isSaccel)
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
		auto bullet = new cBullet(imageName, pos, dir, D3DXToDegree(atan2(dir.y, dir.x)) + 90, bulletSpd, size, isHoming, isFaccel, isSaccel);
		bullet->SetName(bulletName);
		bullet->m_atk = atk;

		if (bulletName == "PlayerBullet")
			m_pBullet.push_back(bullet);
		else if (strstr(bulletName.c_str(), "Enemy") != nullptr)
			m_eBullet.push_back(bullet);
		newRot -= theta;
	}
}

void cBulletManager::N_Straight_Tan(const string& bulletName, const string& imageName, int n, int length, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isFaccel, bool isSaccel)
{
	float rot = D3DXToDegree(atan2(dir.y, dir.x));

	if (n % 2) pos.x -= n / 2 * length;
	else pos.x -= n / 2 * length - length / 2;

	for (size_t i = 0; i < n; ++i) {
		auto bullet = new cBullet(imageName, VEC2(pos.x + i * length, pos.y), dir, rot + 90, bulletSpd, size, false, isFaccel, isSaccel);
		bullet->SetName(bulletName);
		bullet->m_atk = atk;
		if (bulletName == "PlayerBullet")
			m_pBullet.push_back(bullet);
		else if (strstr(bulletName.c_str(), "Enemy") != nullptr)
			m_eBullet.push_back(bullet);
	}
}

