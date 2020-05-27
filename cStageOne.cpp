#include "DXUT.h"
#include "cScroolMap.h"
#include "cStageOne.h"

cStageOne::cStageOne()
{
	m_map = new cScroolMap(IMAGE->FindTexture("StageOneBG"));
}

cStageOne::~cStageOne()
{
	SAFE_DELETE(m_map);
}

void cStageOne::Init()
{
	SOUND->Play("StageBGM", true);
	OBJFIND(PLAYER)->SetActive(true);
}

void cStageOne::Update()
{
	Lerp<VEC2>(CAMERA->m_pos, CAMERA->m_pos, OBJFIND(PLAYER)->GetPos(), 0.05);
	m_map->Update();

	Pause();
}

void cStageOne::Render()
{
	m_map->Render();
}

void cStageOne::Release()
{
	SOUND->Stop("StageBGM");
	OBJFIND(PLAYER)->SetActive(false);
}

void cStageOne::Pause()
{
	if (KEYDOWN('P')) {
		GAME->m_isPause = !GAME->m_isPause;
		if (GAME->m_isPause) {
			GAME->OLD_TIME_SCALE = GAME->TIME_SCALE;
			GAME->TIME_SCALE = 0.f;
		}
		else {
			GAME->TIME_SCALE = GAME->OLD_TIME_SCALE;
		}
	}
}
