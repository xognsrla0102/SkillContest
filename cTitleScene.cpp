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
	CAMERA->m_pos = VEC2(WINSIZEX / 2, WINSIZEY / 2);
}

void cTitleScene::Update()
{
}

void cTitleScene::Render()
{
	IMAGE->Render(m_bg->m_text, VEC2(0, 0));
}

void cTitleScene::Release()
{
	SOUND->Stop("TitleBGM");
}
