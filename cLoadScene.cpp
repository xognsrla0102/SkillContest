#include "DXUT.h"
#include "cPlayer.h"
#include "cBulletManager.h"

#include "cTitleScene.h"
#include "cStageOne.h"

#include "cLoadScene.h"

cLoadScene::cLoadScene()
{
	IMAGE->AddTexture("LoadBG", "resources/image/load/bg.png");
	m_bg = new cImage;
	m_bg->m_text = IMAGE->FindTexture("LoadBG");
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
	//BGM 로드
	Load("TitleBGM", L"resources/bgm/title.wav");
	Load("StageBGM", L"resources/bgm/stage.wav");
	Load("MidBossBGM", L"resources/bgm/midboss.wav");
	Load("LastBossBGM", L"resources/bgm/lastboss.wav");
	Load("OneEndingBGM", L"resources/bgm/oneending.wav");
	Load("TwoEndingBGM", L"resources/bgm/twoending.wav");
	Load("FailBGM", L"resources/bgm/fail.wav");
	Load("RankBGM", L"resources/bgm/rank.wav");

	//효과음 로드
	Load("Bullet0SND", L"resources/sound/bullet0.wav");
	Load("Bullet1SND", L"resources/sound/bullet1.wav");
	Load("Explosion0SND", L"resources/sound/explosion0.wav");
	Load("Explosion1SND", L"resources/sound/explosion1.wav");
	Load("Explosion2SND", L"resources/sound/explosion2.wav");
	Load("CountSND", L"resources/sound/count.wav");
	Load("HitSND", L"resources/sound/hit.wav");
	Load("ShieldSND", L"resources/sound/shield.wav");

	//이미지 로드
	Load("TitleBG", "resources/image/title/title.png");
	Load("StageOneBG", "resources/image/stageone/bg/bg.png");

	Load("PlayerIMG", "resources/image/player/player.png");
	Load("PlayerBullet0IMG", "resources/image/bullet/playerbullet0.png");
	Load("PlayerBullet1IMG", "resources/image/bullet/playerbullet1.png");
	Load("PlayerBullet2IMG", "resources/image/bullet/playerbullet2.png");

	//UI
	Load("IngameBGUI", "resources/image/ui/ingame/bg.png");
	Load("IngameWeaponUI", "resources/image/ui/ingame/nowweapon.png");
	Load("IngameStarUI", "resources/image/ui/ingame/star.png");
}

void cLoadScene::Update()
{
	//소리
	if (m_nowLoad[0] < m_sounds.size()) {
		int& idx = m_nowLoad[0];
		SOUND->AddSound(m_sounds[idx]->m_idx1, m_sounds[idx]->m_idx2);
		idx++;
	}

	//이미지
	if (m_nowLoad[1] < m_imgs.size()) {
		int& idx = m_nowLoad[1];
		IMAGE->AddTexture(m_imgs[idx]->m_idx1, m_imgs[idx]->m_idx2, m_imgs[idx]->m_cnt);
		idx++;
	}

	if (m_nowLoad[0] == m_sounds.size() &&
		m_nowLoad[1] == m_imgs.size()
		) {
		UI->Init();
		//OBJ생성
		OBJECT->AddOBJ(new cPlayer, PLAYER);
		OBJECT->AddOBJ(new cBulletManager, BULLET);
		//OBJECT->AddOBJ(new cEnemyAdmin, ENEMYS);
		//OBJECT->AddOBJ(new cItemAdmin, ITEMS);

		SCENE->AddScene("TitleScene", new cTitleScene);
		SCENE->AddScene("StageOneScene", new cStageOne);
		SCENE->ChangeSceneEffect();
		SCENE->ChangeScene("TitleScene");
	}
}

void cLoadScene::Render()
{
	IMAGE->Render(m_bg->m_text, VEC2(0, 0));
}

void cLoadScene::Release()
{
}