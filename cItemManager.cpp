#include "DXUT.h"
#include "cItem.h"
#include "cItemManager.h"

cItemManager::~cItemManager()
{
	Release();
}

void cItemManager::Update()
{
	size_t size = m_items.size();
	for (size_t i = 0; i < size; i++) {
		m_items[i]->Update();
		m_items[i]->OutMapChk(200);
		m_items[i]->Collision();

		if (m_items[i]->GetLive() == FALSE) {
			SAFE_DELETE(m_items[i]);
			m_items.erase(m_items.begin() + i);
			i--, size--;
		}
	}
}

void cItemManager::Render()
{
	for (auto iter : m_items)
		iter->Render();
}

void cItemManager::Release()
{
	for (auto iter : m_items)
		SAFE_DELETE(iter);
	m_items.clear();
}

