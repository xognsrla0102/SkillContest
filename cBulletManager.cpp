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
	for (auto iter : m_bullets)
		iter->Update();
}

void cBulletManager::Render()
{
	for (auto iter : m_bullets)
		iter->Render();
}

void cBulletManager::Reset()
{
	for (auto iter : m_bullets)
		SAFE_DELETE(iter);
}
