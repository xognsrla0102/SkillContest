#include "DXUT.h"
//#include "cItem.h"
//#include "cItemAdmin.h"
#include "cEnemy.h"
#include "cEnemyManager.h"

cEnemyManager::cEnemyManager()
{
}

cEnemyManager::~cEnemyManager()
{
	Release();
}

void cEnemyManager::Update()
{
	size_t size = m_meteor.size();
	for (size_t i = 0; i < size; ++i) {
		m_meteor[i]->Update();
		if (m_meteor[i]->GetLive() == false) {
			SAFE_DELETE(m_meteor[i]);
			m_meteor.erase(m_meteor.begin() + i);
			--i, --size;
		}
	}

	size = m_enemy.size();
	for (size_t i = 0; i < size; ++i) {
		m_enemy[i]->Update();
		if (m_enemy[i]->GetLive() == false) {
			SAFE_DELETE(m_enemy[i]);
			m_enemy.erase(m_enemy.begin() + i);
			--i, --size;
		}
	}
}

void cEnemyManager::Render()
{
	for (auto iter : m_meteor)
		iter->Render();
	for (auto iter : m_enemy)
		iter->Render();

	//if (m_mBoss) m_mBoss->Render();
	//if (m_boss) m_boss->Render();
}


void cEnemyManager::Release()
{
	for (auto iter : m_meteor)
		SAFE_DELETE(iter);
	m_meteor.clear();
	for (auto iter : m_enemy)
		SAFE_DELETE(iter);
	m_enemy.clear();

	SAFE_DELETE(m_boss);
	SAFE_DELETE(m_mBoss);
}

