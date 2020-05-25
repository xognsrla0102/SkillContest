#include "DXUT.h"
#include "cPlayer.h"
#include "cStageOne.h"

cStageOne::cStageOne()
{
	m_bg1 = m_bg2 = IMAGE->FindTexture("StageOneBG");
}

cStageOne::~cStageOne()
{
}

void cStageOne::Init()
{
	SOUND->Play("StageBGM", TRUE);

	cObject* m_player = OBJECT->Create("player", VEC2(winSizeX / 2, winSizeY - 100), 1, OBJ_Tag::PLAYER);
	m_player->AddComponent<cRenderer>();
	m_player->AddComponent<cPlayer>();

	bgPos1 = VEC2(0, -(FLOAT)m_bg1->info.Height);
	bgPos2 = VEC2(0, 0);
}

void cStageOne::Update()
{
	if (bgPos1.y > 0) {
		bgPos1 = VEC2(0, -(FLOAT)m_bg1->info.Height);
		bgPos2 = VEC2(0, 0);
	}
	else {
		bgPos1.y += 10;
		bgPos2.y += 10;
	}
}

void cStageOne::Render()
{
	IMAGE->Render(m_bg1, bgPos1, VEC2(1, 1));
	IMAGE->Render(m_bg2, bgPos2, VEC2(1, 1));
}

void cStageOne::Release()
{
}
