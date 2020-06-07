#include "DXUT.h"
#include "cIngameUI.h"
#include "cPlayer.h"
#include "cGameManager.h"

cGameManager::cGameManager()
{
	Init();
}

cGameManager::~cGameManager()
{
}

void cGameManager::Init()
{
	OLD_TIME_SCALE = 1.f;
	TIME_SCALE = 1.f;

	m_expMax = 2500;
	m_nowExp = 0;

	m_score = 0;

	m_level = 1;

	m_isPause = false;
	m_isNotDead = false;
	m_isDebugInfo = false;

	m_learnBullet1 = 0;
	m_learnBullet2 = 0;
	m_learnBullet3 = 0;
}

void cGameManager::Update()
{
	if (KEYDOWN(VK_ESCAPE)) {
		m_isPause = !m_isPause;
		if (m_isPause) {
			OLD_TIME_SCALE = TIME_SCALE;
			TIME_SCALE = 0.f;
		}
		else {
			TIME_SCALE = OLD_TIME_SCALE;
		}
	}

	if (m_isPause) return;

	if (KEYDOWN(VK_F1)) m_isNotDead = !m_isNotDead;
	if (KEYDOWN(VK_F2)) if(m_level != 5) m_nowExp = m_expMax;

	if (m_level < 5 && m_nowExp >= m_expMax) {
		m_level++;
		m_nowExp -= m_expMax;

		auto player = (cPlayer*)OBJFIND(PLAYER);

		switch (m_level) {
		case 2:
			m_expMax = 4000;
			break;
		case 3:
			m_expMax = 5500;
			break;
		case 4:
			m_expMax = 7000;
			break;
		}

		if (m_level == 5) m_nowExp = 0;
		player->m_hpMax += player->m_hp * 0.2;

		for (int i = 0; i < 2; ++i) {
			player->m_fireDelay[i] -= player->m_fireDelay[i] * 0.2f;
			player->m_atk[i] += player->m_atk[i] * 0.2f;
		}
		if(player->m_nowWeapon != 2) player->m_fire->m_delay = player->m_fireDelay[player->m_nowWeapon];
		player->m_hp = player->m_hpMax;

		auto ingameUI = ((cIngameUI*)UI->FindUI("IngameSceneUI"));

		ingameUI->m_targetPos = VEC2(688, 595);
		Lerp(ingameUI->m_targetPos, VEC2(688, 399), (player->m_hpMax - player->m_hp) / (double)player->m_hpMax);

		VEC2 pos = OBJFIND(PLAYER)->GetPos();
		FONT->AddFont("Level UP!!!", VEC2(pos.x - 40, pos.y - 50), 1.f, true, D3DCOLOR_XRGB(255, 255, 0));
	}

	if (KEYDOWN(VK_F3)) {
		((cItemManager*)OBJFIND(ITEM))->m_items.push_back(
			new cItem("ItemHpIMG", GXY(GAMESIZEX / 2, -100), GXY(GAMESIZEX / 2, -100))
		);
	}

	if (KEYDOWN(VK_F7)) {
		m_isDebugInfo = !m_isDebugInfo;
	}
}

