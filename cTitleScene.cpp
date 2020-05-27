#include "DXUT.h"
#include "cTitleScene.h"

cTitleScene::cTitleScene()
{
	m_bg = new cImage;
	m_bg->m_text = IMAGE->FindTexture("TitleBG");
}

cTitleScene::~cTitleScene()
{
	SAFE_DELETE(m_bg);
}

void cTitleScene::Init()
{
	SOUND->Play("TitleBGM", true);
}

void cTitleScene::Update()
{
	if (KEYDOWN(VK_RETURN)) {
		SCENE->ChangeSceneEffect(40.f);
		SCENE->ChangeScene("StageOneScene");
	}
}

void cTitleScene::Render()
{
	IMAGE->Render(m_bg->m_text, VEC2(0, 0));
}

void cTitleScene::Release()
{
	SOUND->Stop("TitleBGM");
}
