#include "DXUT.h"
#include "cPlayer.h"
#include "cBulletManager.h"
#include "cEnemyManager.h"

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

	Load("Shot0SND", L"resources/sound/shot0.wav");
	Load("Shot1SND", L"resources/sound/shot1.wav");
	Load("Shot2SND", L"resources/sound/shot2.wav");
	Load("Shot3SND", L"resources/sound/shot3.wav");

	Load("ShotGun0SND", L"resources/sound/shotgun0.wav");

	Load("Explosion0SND", L"resources/sound/explosion0.wav");
	Load("Explosion1SND", L"resources/sound/explosion1.wav");
	Load("Explosion2SND", L"resources/sound/explosion2.wav");
	Load("Explosion3SND", L"resources/sound/explosion3.wav");
	Load("Explosion4SND", L"resources/sound/explosion4.wav");
	Load("Explosion5SND", L"resources/sound/explosion5.wav");

	Load("CountSND", L"resources/sound/count.wav");
	Load("HitSND", L"resources/sound/hit.wav");

	//이미지 로드
	Load("TitleBG", "resources/image/title/title.png");
	Load("StageOneBG", "resources/image/stageone/bg/bg.png");

	Load("PlayerIdle", "resources/image/player/idle.png");
	Load("PlayerLeft", "resources/image/player/left%d.png", 5);
	Load("PlayerRight", "resources/image/player/Right%d.png", 5);

	Load("PlayerBullet0IMG", "resources/image/bullet/playerBullet0.png");
	Load("PlayerBullet1IMG", "resources/image/bullet/playerbullet1.png");
	Load("PlayerBullet2IMG", "resources/image/bullet/playerbullet2.png");
	Load("PlayerBullet3IMG", "resources/image/bullet/playerbullet3.png");

	Load("EnemyMeteor0IMG", "resources/image/enemy/meteor/meteor0.png");
	Load("EnemyMeteor1IMG", "resources/image/enemy/meteor/meteor1.png");
	Load("EnemyMeteor2IMG", "resources/image/enemy/meteor/meteor2.png");
	Load("EnemyMeteor3IMG", "resources/image/enemy/meteor/meteor3.png");
	Load("EnemyMeteor4IMG", "resources/image/enemy/meteor/meteor4.png");
	Load("EnemyMeteor5IMG", "resources/image/enemy/meteor/meteor5.png");

	Load("Explosion0IMG", "resources/image/effect/explosion/0/%d.png", 24);
	Load("Explosion8IMG", "resources/image/effect/explosion/8/%d.png", 32);
	Load("Explosion9IMG", "resources/image/effect/explosion/9/%d.png", 32);
	Load("Explosion10IMG", "resources/image/effect/explosion/10/%d.png", 24);

	//UI
	Load("num_dot", "resources/image/ui/num/dot.png");

	char str1[256], str2[256];
	for (int i = 0; i < 10; ++i) {
		sprintf(str1, "num_%d", i);
		sprintf(str2, "resources/image/ui/num/%d.png", i);
		Load(str1, str2);
	}

	Load("IngameBGUI", "resources/image/ui/ingame/bg.png");
	Load("IngameWeaponUI", "resources/image/ui/ingame/nowweapon.png");
	Load("IngameStarUI", "resources/image/ui/ingame/star.png");
	Load("IngameExpUI", "resources/image/ui/ingame/exp_bar.png");
	Load("IngameHpUI", "resources/image/ui/ingame/hp_bar.png");
	Load("IngameLevelUI", "resources/image/ui/ingame/level.png");
	Load("IngameSkillUI", "resources/image/ui/ingame/skill_bar.png");
	Load("IngameNoSkillUI", "resources/image/ui/ingame/noskill.png");
	Load("IngameBackWhiteUI", "resources/image/ui/ingame/backwhite.png");
	Load("IngameDamagedUI", "resources/image/ui/ingame/damaged.png");
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
		OBJECT->AddOBJ(new cEnemyManager, ENEMY);
		//OBJECT->AddOBJ(new cItemAdmin, ITEM);

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