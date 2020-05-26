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
	CAMERA->m_isShake = TRUE;
	SOUND->Play("StageBGM", true);
}

void cStageOne::Update()
{
	m_map->Update();
}

void cStageOne::Render()
{
	m_map->Render();
}

void cStageOne::Release()
{
	SOUND->Stop("StageBGM");
}
