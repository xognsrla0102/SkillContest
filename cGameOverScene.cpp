#include "DXUT.h"
#include "cGameOverScene.h"

cGameOverScene::cGameOverScene()
{
	m_bg = new cImage;
}

cGameOverScene::~cGameOverScene()
{
	SAFE_DELETE(m_bg);
}

void cGameOverScene::Init()
{
	SOUND->Play("FailBGM", true);
	m_bg->m_text = IMAGE->FindTexture("GameOverBG");
	CAMERA->m_pos = VEC2(WINSIZEX / 2, WINSIZEY / 2);
}

void cGameOverScene::Update()
{
	for(int i = 0; i < 256; ++i)
		if (KEYDOWN(i)) {
			SCENE->ChangeScene("TitleScene", "Fade", 20.f);
		}
}

void cGameOverScene::Render()
{
	IMAGE->Render(m_bg->m_text, VEC2(0, 0));
}

void cGameOverScene::Release()
{
	SOUND->Stop("FailBGM");
}
