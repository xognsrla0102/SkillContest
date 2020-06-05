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

	if (m_level < 5 && KEYDOWN('A')) {
		m_nowExp += 1000;
		m_totalExp += 1000;
	}

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

		player->m_hpMax += player->m_hp * 0.2;

		for (int i = 0; i < 5; ++i) {
			player->m_fireDelay[i] -= player->m_fireDelay[i] * 0.2f;
			player->m_atk[i] += player->m_atk[i] * 0.2f;
		}
		player->m_fire->m_delay = player->m_fireDelay[player->m_nowWeapon];
		player->m_hp = player->m_hpMax;

		auto ingameUI = ((cIngameUI*)UI->FindUI("IngameSceneUI"));

		ingameUI->m_targetPos = VEC2(688, 595);
		Lerp(ingameUI->m_targetPos, VEC2(688, 399), (player->m_hpMax - player->m_hp) / (double)player->m_hpMax);

		VEC2 pos = OBJFIND(PLAYER)->GetPos();
		FONT->AddFont("Level UP!!!", VEC2(pos.x - 40, pos.y - 50), 1.f, true);
	}
}

