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

	CAMERA->m_pos = VEC2(OBJFIND(PLAYER)->GetPos().x + 300, OBJFIND(PLAYER)->GetPos().y);
}

void cStageOne::Update()
{
	CameraMove();

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

void cStageOne::CameraMove()
{
	Lerp<VEC2>(CAMERA->m_pos, CAMERA->m_pos, VEC2(OBJFIND(PLAYER)->GetPos().x + 300, OBJFIND(PLAYER)->GetPos().y), 0.05);

	if (CAMERA->m_pos.x < 590) CAMERA->m_pos.x = 590;
	else if (CAMERA->m_pos.x > 3840) CAMERA->m_pos.x = 3840;

	if (CAMERA->m_pos.y < 310) CAMERA->m_pos.y = 310;
	else if (CAMERA->m_pos.y > 1845) CAMERA->m_pos.y = 1845;
}
