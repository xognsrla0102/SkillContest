#include "DXUT.h"
#include "cHelpScene.h"

cHelpScene::cHelpScene()
{
	m_bg = new cImage;
	m_bg->m_text = IMAGE->FindTexture("HelpBG");
}

cHelpScene::~cHelpScene()
{
	SAFE_DELETE(m_bg);
}

void cHelpScene::Init()
{
	SOUND->Play("HelpBGM", true);
}

void cHelpScene::Update()
{
	if (KEYDOWN(VK_RETURN))
		SCENE->ChangeScene("TitleScene", "Fade", 10.f);
}

void cHelpScene::Render()
{
	IMAGE->Render(m_bg->m_text, VEC2(0, 0));
}

void cHelpScene::Release()
{
	SOUND->Stop("HelpBGM");
}
