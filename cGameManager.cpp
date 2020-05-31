#include "DXUT.h"
#include "cPlayer.h"
#include "cTimer.h"
#include "cGameManager.h"

cGameManager::cGameManager()
{
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
	m_totalExp = 0;

	m_level = 1;

	m_isPause = false;
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

	if (KEYPRESS(VK_ADD) && TIME_SCALE < 5.f) {
		TIME_SCALE += 0.1f;
		if (TIME_SCALE > 5.f) TIME_SCALE = 5.f;
	}
	if (KEYPRESS(VK_SUBTRACT) && TIME_SCALE > 0) {
		TIME_SCALE -= 0.1f;
		if (TIME_SCALE < 0) TIME_SCALE = 0.f;
	}

	if (m_level < 5 && KEYDOWN('A')) {
		m_nowExp += 100;
		m_totalExp += 100;
	}

	if (m_level < 5 && m_nowExp >= m_expMax) {
		m_level++;

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

		player->m_hpMax += player->m_hp * 0.2;

		for (int i = 0; i < 5; ++i) {
			player->m_fireDelay[i] -= player->m_fireDelay[i] * 0.2f;
			player->m_atk[i] += player->m_atk[i] * 0.2f;
		}
		player->m_fire->m_delay = player->m_fireDelay[player->m_nowWeapon];

		m_nowExp = 0;
		player->m_hp = player->m_hpMax;

		VEC2 pos = OBJFIND(PLAYER)->GetPos();
		FONT->AddFont("Level UP!!!", VEC2(pos.x - 40, pos.y - 50), 1.f, true);
	}
}

