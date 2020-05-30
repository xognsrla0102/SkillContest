#include "DXUT.h"
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
	if (!m_isPause) {
		if (KEYPRESS(VK_ADD) && TIME_SCALE < 5.f) {
			TIME_SCALE += 0.1f;
			if (TIME_SCALE > 5.f) TIME_SCALE = 5.f;
		}
		if (KEYPRESS(VK_SUBTRACT) && TIME_SCALE > 0) {
			TIME_SCALE -= 0.1f;
			if (TIME_SCALE < 0) TIME_SCALE = 0.f;
		}
	}

	if (KEYDOWN('A')) {
		m_nowExp += 100;
		m_totalExp += 100;
	}

	switch (m_level) {
	case 1:
		if (m_expMax != 2500) m_expMax = 2500;
		break;
	case 2:
		if (m_expMax != 4000) m_expMax = 4000;
		break;
	case 3:
		if (m_expMax != 7000) m_expMax = 7000;
		break;
	case 4:
		if (m_expMax != 10000) m_expMax = 10000;
		break;
	}

	if (m_level < 5 && m_nowExp >= m_expMax) {
		m_nowExp = 0;
		m_level++;
		VEC2 pos = OBJFIND(PLAYER)->GetPos();

		FONT->AddFont("Level UP!!!", VEC2(pos.x - 10, pos.y - 10), 1.f, true);
	}
}

