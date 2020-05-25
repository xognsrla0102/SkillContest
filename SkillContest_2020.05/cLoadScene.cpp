#include "DXUT.h"
#include "cTitleScene.h"
#include "cStageOne.h"
#include "cLoadScene.h"

cLoadScene::cLoadScene()
{
	IMAGE->AddTexture("LoadBG", "resources/image/loading/load.png");
	m_bg = IMAGE->FindTexture("LoadBG");
}

cLoadScene::~cLoadScene()
{
}

void cLoadScene::Init()
{
	LoadSnd("TitleBGM", L"resources/bgm/title.wav");
	LoadSnd("StageBGM", L"resources/bgm/stage.wav");

	LoadImg("TitleBG", "resources/image/title/title.png");
	LoadImg("StageOneBG", "resources/image/stageone/bg/bg.png");

	LoadImg("player", "resources/image/player/player", 1);

	SCENE->AddScene("TitleScene", new cTitleScene);
	SCENE->AddScene("StageOneScene", new cStageOne);

	SCENE->ChangeSceneEffect();
	SCENE->ChangeScene("TitleScene");
}

void cLoadScene::Update()
{
}

void cLoadScene::Render()
{
	IMAGE->Render(m_bg, VEC2(0, 0), VEC2(1, 1));
}

void cLoadScene::Release()
{
}

void cLoadScene::LoadImg(string key, string path, INT amount)
{
	//0�� ��� ���� �̹����� �Ǵ�
	//Player, player.png ���� ���
	if (amount == 0) {
		IMAGE->AddTexture(key.c_str(), path.c_str());
	}

	//amount 1�ϰ�� �ϳ��� �̹����� �ִϸ��̼����� �Ǵ�
	//Player0 ~ n, player0 ~ n.png ���� ���
	else {
		for (int i = 0; i < amount; ++i) {
			char _path[256], _key[256];
			sprintf(_path, "%s%d.png", path.c_str(), i);
			sprintf(_key, "%s%d", key.c_str(), i);
			IMAGE->AddTexture(_key, _path);
		}
	}
}

void cLoadScene::LoadSnd(string key, wstring path)
{
	SOUND->AddSound(key, path);
}