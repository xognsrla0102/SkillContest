#include "DXUT.h"
#include "cTitleScene.h"
#include "cStageOne.h"
#include "cLoadScene.h"

cLoadScene::cLoadScene()
{
	IMAGE->AddTexture("LoadBG", "resources/image/load/bg.png");
	m_bg = new cImage;
	m_bg->m_img = IMAGE->FindTexture("LoadBG");
}

cLoadScene::~cLoadScene()
{
	SAFE_DELETE(m_bg);

	for (auto iter : m_sounds)
		SAFE_DELETE(iter);
	m_sounds.clear();

	for (auto iter : m_imgs)
		SAFE_DELETE(iter);
	m_imgs.clear();
}

void cLoadScene::Init()
{
	Load("TitleBGM", L"resources/bgm/title.wav");
	Load("StageBGM", L"resources/bgm/stage.wav");

	Load("TitleBG", "resources/image/title/title.png");
	Load("StageOneBG", "resources/image/stageone/bg/bg.png");
}

void cLoadScene::Update()
{
	//家府
	if (m_nowLoad[0] < m_sounds.size()) {
		int& idx = m_nowLoad[0];
		SOUND->AddSound(m_sounds[idx]->m_idx1, m_sounds[idx]->m_idx2);
		idx++;
	}

	//捞固瘤
	if (m_nowLoad[1] < m_imgs.size()) {
		int& idx = m_nowLoad[1];
		IMAGE->AddTexture(m_imgs[idx]->m_idx1, m_imgs[idx]->m_idx2, m_imgs[idx]->m_cnt);
		idx++;
	}

	if (m_nowLoad[0] == m_sounds.size() &&
		m_nowLoad[1] == m_imgs.size()
		) {
		//OBJ积己
		//OBJECT->AddOBJ(new cPlayer, PLAYER);
		//((cPlayer*)OBJFIND(PLAYER))->Init();
		//OBJECT->AddOBJ(new cBalls, BALLS);
		//OBJECT->AddOBJ(new cBulletAdmin, BULLETS);
		//OBJECT->AddOBJ(new cEnemyAdmin, ENEMYS);
		//OBJECT->AddOBJ(new cItemAdmin, ITEMS);

		SCENE->AddScene("TitleScene", new cTitleScene);
		SCENE->AddScene("StageOneScene", new cStageOne);
		SCENE->ChangeScene("TitleScene");
	}
}

void cLoadScene::Render()
{
	IMAGE->Render(m_bg->m_img, VEC2(0, 0));
}

void cLoadScene::Release()
{
}