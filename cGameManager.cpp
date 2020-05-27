#include "DXUT.h"
#include "cGameManager.h"

cGameManager::cGameManager()
{
}

cGameManager::~cGameManager()
{
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
}
