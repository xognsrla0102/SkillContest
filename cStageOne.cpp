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
	CameraMove();

	m_map->Update();

	Pause();
}

void cStageOne::Render()
{
	m_map->Render();
	IMAGE->Render(OBJFIND(PLAYER)->GetImg(), VEC2(0, 0), VEC2(1, 1), 0.f, true);
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
	//CAMERA->m_pos = VEC2(WINSIZEX / 2, WINSIZEY / 2);

	IMAGE->FindTexture("StageOneBG")->m_info.Width / 2;
	CAMERA->m_pos.x;


	if ((-(IMAGE->FindTexture("StageOneBG")->m_info.Width) / 2) - (WINSIZEX / 2) < OBJFIND(PLAYER)->GetPos().x ||
		((IMAGE->FindTexture("StageOneBG")->m_info.Width) / 2) + (WINSIZEX / 2) > OBJFIND(PLAYER)->GetPos().x ||
		(-(IMAGE->FindTexture("StageOneBG")->m_info.Height) / 2) - (WINSIZEY / 2) < OBJFIND(PLAYER)->GetPos().y ||
		((IMAGE->FindTexture("StageOneBG")->m_info.Height) / 2) + (WINSIZEY / 2) > OBJFIND(PLAYER)->GetPos().y)
		{
		Lerp<VEC2>(CAMERA->m_pos, CAMERA->m_pos, VEC2(OBJFIND(PLAYER)->GetPos().x + 350, OBJFIND(PLAYER)->GetPos().y), 0.05);
		}
	//CAMERA->m_pos.x = GAMESIZEX / 2;

	//if (OBJFIND(PLAYER)->GetPos().x < WINSIZEX / 2) {
		//CAMERA->m_pos.x = WINSIZEX / 2;
	//}
}
