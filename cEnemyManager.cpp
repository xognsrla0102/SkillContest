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
	for (size_t i = 0; i < size; i++) {
		m_meteor[i]->Update();
		if (m_meteor[i]->GetLive() == FALSE) {
			SAFE_DELETE(m_meteor[i]);
			m_meteor.erase(m_meteor.begin() + i);
			i--, size--;
		}
	}
}

void cEnemyManager::Render()
{
	for (auto iter : m_meteor)
		iter->Render();
}


void cEnemyManager::Release()
{
	for (auto iter : m_meteor)
		SAFE_DELETE(iter);
	m_meteor.clear();
}

