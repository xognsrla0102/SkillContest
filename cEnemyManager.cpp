#include "DXUT.h"
//#include "cItem.h"
//#include "cItemAdmin.h"
//#include "cEnemy.h"
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
	//size_t size = m_meteor.size();
	//for (size_t i = 0; i < size; i++) {
	//	m_ones[i]->Update();
	//	m_ones[i]->OutMapChk();

	//	if (m_ones[i]->GetLive() == FALSE) {
	//		VEC2 onePos = m_ones[i]->GetPos();
	//		//∏  æ»ø°º≠ ¡◊æ˙¿ª ∞ÊøÏ∏∏ ¿Ã∆Â∆ÆøÕ ªÁøÓµÂ ≥™∞‘
	//		if (!(50 > onePos.x + 25 || onePos.x - 25 > 50 + INGAMEX ||
	//			50 > onePos.y + 25 || onePos.y - 25 > 50 + INGAMEY)) {
	//			SOUND->Copy("enemydeadSND");
	//			EFFECT->AddEffect(
	//				new cEffect("enemy_dead_EFFECT", 1, onePos, VEC2(0, 0),
	//					VEC2(0.5f, 0.5f), VEC2(1, 1)
	//				)
	//			);
	//			//¡◊¿∏∏È æ∆¿Ã≈€ ∂≥±¿
	//			for (size_t j = 0; j < m_ones[i]->GetItemNames().size(); j++) {
	//				string nowItemName = m_ones[i]->GetItemNames()[j];
	//				((cItemAdmin*)OBJFIND(ITEMS))->m_items.push_back(
	//					new cItem(nowItemName, onePos, VEC2(onePos.x, onePos.y - (40 + rand() % 30)))
	//				);
	//			}
	//		}
	//		SAFE_DELETE(m_ones[i]);
	//		m_ones.erase(m_ones.begin() + i);
	//		i--, size--;
	//	}
	//}
}

void cEnemyManager::Render()
{
	/*for (auto iter : m_meteor)
		iter->Render();*/
}

void cEnemyManager::Release()
{
	for (auto iter : m_meteor)
		SAFE_DELETE(iter);
	m_meteor.clear();
}

