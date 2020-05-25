#include "DXUT.h"
#include "cTitleScene.h"

cTitleScene::cTitleScene()
{
	m_bg = IMAGE->FindTexture("TitleBG");
}

cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{
	SOUND->Play("TitleBGM", TRUE);
}

void cTitleScene::Update()
{
	DEBUG_LOG("%d %d\n", INPUTMANAGER->m_nowKey[VK_UP], INPUTMANAGER->m_pastKey[VK_UP]);
	DEBUG_LOG("%d\n", INPUTMANAGER->IsKeyDown(VK_UP));

	if (INPUTMANAGER->IsKeyDown(VK_UP)) {
		SOUND->Stop("TitleBGM");
		SCENE->ChangeSceneEffect(50.f);
		SCENE->ChangeScene("StageOneScene");
	}
}

void cTitleScene::Render()
{
	IMAGE->Render(m_bg, VEC2(0, 0), VEC2(1, 1), 0.f);
}

void cTitleScene::Release()
{
}