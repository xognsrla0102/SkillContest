#include "DXUT.h"
#include "cPlayer.h"
#include "cBulletManager.h"
#include "cEnemyManager.h"

#include "cTitleScene.h"
#include "cGameOverScene.h"
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
	Load("ResultBGM", L"resources/bgm/result.wav");

	//효과음 로드

	//피격음

	//레이저 피격음
	Load("RazerHit0SND", L"resources/sound/hit/razer_hit0.wav");
	Load("RazerHit1SND", L"resources/sound/hit/razer_hit1.wav");
	Load("RazerHit2SND", L"resources/sound/hit/razer_hit2.wav");
	Load("RazerHit3SND", L"resources/sound/hit/razer_hit3.wav");
	Load("RazerHit4SND", L"resources/sound/hit/razer_hit4.wav");
	Load("RazerHit5SND", L"resources/sound/hit/razer_hit5.wav");

	//총알 피격음
	Load("RocketHit0SND", L"resources/sound/hit/rocket_hit0.wav");
	Load("RocketHit1SND", L"resources/sound/hit/rocket_hit1.wav");
	Load("RocketHit2SND", L"resources/sound/hit/rocket_hit2.wav");
	Load("RocketHit3SND", L"resources/sound/hit/rocket_hit3.wav");
	Load("RocketHit4SND", L"resources/sound/hit/rocket_hit4.wav");

	//배 피격음
	Load("ShipHit0SND", L"resources/sound/hit/ship_hit0.wav");
	Load("ShipHit1SND", L"resources/sound/hit/ship_hit1.wav");
	Load("ShipHit2SND", L"resources/sound/hit/ship_hit2.wav");
	Load("ShipHit3SND", L"resources/sound/hit/ship_hit3.wav");
	Load("ShipHit4SND", L"resources/sound/hit/ship_hit4.wav");
	Load("ShipHit5SND", L"resources/sound/hit/ship_hit5.wav");
	Load("ShipHit6SND", L"resources/sound/hit/ship_hit6.wav");

	//돌 피격음
	Load("RockHit0SND", L"resources/sound/hit/rock_hit0.wav");
	Load("RockHit1SND", L"resources/sound/hit/rock_hit1.wav");
	Load("RockHit2SND", L"resources/sound/hit/rock_hit2.wav");
	Load("RockHit3SND", L"resources/sound/hit/rock_hit3.wav");

	//적 피격음
	Load("EnemyHit0SND", L"resources/sound/hit/enemy_hit0.wav");
	Load("EnemyHit1SND", L"resources/sound/hit/enemy_hit1.wav");
	Load("EnemyHit2SND", L"resources/sound/hit/enemy_hit2.wav");
	Load("EnemyHit3SND", L"resources/sound/hit/enemy_hit3.wav");

	//플레이어 피격음
	Load("PlayerHitSND", L"resources/sound/hit/player_hit.wav");

	//발사음
	Load("EnemyFireSND", L"resources/sound/fire/enemy_fire.wav");

	Load("RazerChargeSND", L"resources/sound/fire/razer_charge.wav");
	Load("RazerFireSND", L"resources/sound/fire/razer_fire.wav");

	Load("RocketChargeSND", L"resources/sound/fire/rocket_charge.wav");
	Load("RocketLaunchSND", L"resources/sound/fire/rocket_launch.wav");
	Load("RocketDropSND", L"resources/sound/fire/rocket_drop.wav");

	//무기 0
	Load("Weapon0_0SND", L"resources/sound/fire/weapon0_0.wav");
	Load("Weapon0_1SND", L"resources/sound/fire/weapon0_1.wav");
	Load("Weapon0_2SND", L"resources/sound/fire/weapon0_2.wav");
	Load("Weapon0_3SND", L"resources/sound/fire/weapon0_3.wav");
	Load("Weapon0_4SND", L"resources/sound/fire/weapon0_4.wav");
	Load("Weapon0_5SND", L"resources/sound/fire/weapon0_5.wav");
	Load("Weapon0_6SND", L"resources/sound/fire/weapon0_6.wav");
	Load("Weapon0_7SND", L"resources/sound/fire/weapon0_7.wav");
	Load("Weapon0_8SND", L"resources/sound/fire/weapon0_8.wav");

	//무기 1
	Load("Weapon1_0SND", L"resources/sound/fire/weapon1_0.wav");
	Load("Weapon1_1SND", L"resources/sound/fire/weapon1_1.wav");
	Load("Weapon1_2SND", L"resources/sound/fire/weapon1_2.wav");
	Load("Weapon1_3SND", L"resources/sound/fire/weapon1_3.wav");

	//기타 사운드
	Load("Dash0SND", L"resources/sound/dash0.wav");
	Load("Dash1SND", L"resources/sound/dash1.wav");

	Load("BossSND", L"resources/sound/boss.wav");
	Load("DetectedSND", L"resources/sound/detected.wav");
	Load("NoSkillSND", L"resources/sound/noskill.wav");
	Load("StealSND", L"resources/sound/steal.wav");
	Load("WarningSND", L"resources/sound/warning.wav");

	//이미지 로드
	Load("TitleBG", "resources/image/title/bg.png");
	Load("StageOneBG", "resources/image/stageone/bg/bg.png");
	Load("GameOverBG", "resources/image/gameover/bg.png");

	Load("PlayerIdle", "resources/image/player/idle.png");
	Load("PlayerLeft", "resources/image/player/left%d.png", 5);
	Load("PlayerRight", "resources/image/player/Right%d.png", 5);
	Load("PlayerCore", "resources/image/player/core.png");

	Load("PlayerBullet0IMG", "resources/image/bullet/playerBullet0.png");
	Load("PlayerBullet1IMG", "resources/image/bullet/playerbullet1.png");

	Load("EnemyRazerIMG", "resources/image/bullet/razer.png");
	Load("EnemyStraightIMG", "resources/image/bullet/straight.png");
	Load("EnemyRadialIMG", "resources/image/bullet/radial.png");

	Load("EnemyMeteor0IMG", "resources/image/enemy/meteor/meteor0.png");
	Load("EnemyMeteor1IMG", "resources/image/enemy/meteor/meteor1.png");
	Load("EnemyMeteor2IMG", "resources/image/enemy/meteor/meteor2.png");
	Load("EnemyMeteor3IMG", "resources/image/enemy/meteor/meteor3.png");
	Load("EnemyMeteor4IMG", "resources/image/enemy/meteor/meteor4.png");
	Load("EnemyMeteor5IMG", "resources/image/enemy/meteor/meteor5.png");

	Load("EnemyStage1_StraightIMG", "resources/image/enemy/stage1/straight.png");
	Load("EnemyStage1_RotateIMG", "resources/image/enemy/stage1/rotate.png");
	Load("EnemyStage1_RazerIMG", "resources/image/enemy/stage1/razer.png");
	Load("EnemyStage1_RadialIMG", "resources/image/enemy/stage1/radial.png");
	Load("EnemyStage1_MidBossIMG", "resources/image/enemy/stage1/midboss.png");
	Load("EnemyStage1_BossIMG", "resources/image/enemy/stage1/lastboss.png");

	Load("EnemyStage2_StraightIMG", "resources/image/enemy/stage2/straight.png");
	Load("EnemyStage2_RotateIMG", "resources/image/enemy/stage2/rotate.png");
	Load("EnemyStage2_RazerIMG", "resources/image/enemy/stage2/razer.png");
	Load("EnemyStage2_RadialIMG", "resources/image/enemy/stage2/radial.png");
	Load("EnemyStage2_MidBossIMG", "resources/image/enemy/stage2/midboss.png");
	Load("EnemyStage2_BossIMG", "resources/image/enemy/stage2/lastboss.png");

	Load("Explosion0IMG", "resources/image/effect/explosion/0/%d.png", 24);
	Load("Explosion1IMG", "resources/image/effect/explosion/1/%d.png", 24);
	Load("Explosion2IMG", "resources/image/effect/explosion/2/%d.png", 23);
	Load("Explosion3IMG", "resources/image/effect/explosion/3/%d.png", 24);
	Load("Explosion4IMG", "resources/image/effect/explosion/4/%d.png", 24);
	Load("Explosion5IMG", "resources/image/effect/explosion/5/%d.png", 32);
	Load("Explosion6IMG", "resources/image/effect/explosion/6/%d.png", 32);
	Load("Explosion7IMG", "resources/image/effect/explosion/7/%d.png", 32);
	Load("Explosion8IMG", "resources/image/effect/explosion/8/%d.png", 32);
	Load("Explosion9IMG", "resources/image/effect/explosion/9/%d.png", 32);
	Load("Explosion10IMG", "resources/image/effect/explosion/10/%d.png", 24);

	Load("ChargeRazerIMG", "resources/image/effect/chargeRazerEffect/%d.png", 24);

	//Load("ShadowIMG", "resources/image/ingame/planet/shadow/%d.png", 17);
	//Load("PlanetIMG", "resources/image/ingame/planet/%d.png", 19);
	Load("CloudIMG", "resources/image/ingame/%d.png", 4);

	//UI
	Load("num_dot", "resources/image/ui/num/dot.png");

	char str1[256], str2[256];
	for (int i = 0; i < 10; ++i) {
		sprintf(str1, "num_%d", i);
		sprintf(str2, "resources/image/ui/num/%d.png", i);
		Load(str1, str2);
	}

	//INGAME UI
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

	//TITLE UI
	Load("TitleNameUI", "resources/image/ui/title/titleName.png");
	Load("TitleStartUI", "resources/image/ui/title/start.png");
	Load("TitleRankUI", "resources/image/ui/title/rank.png");
	Load("TitleHelpUI", "resources/image/ui/title/help.png");
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
		//OBJ생성
		OBJECT->AddOBJ(new cPlayer, PLAYER);
		OBJECT->AddOBJ(new cBulletManager, BULLET);
		OBJECT->AddOBJ(new cEnemyManager, ENEMY);
		//OBJECT->AddOBJ(new cItemAdmin, ITEM);

		SCENE->AddScene("TitleScene", new cTitleScene);
		SCENE->AddScene("StageOneScene", new cStageOne);
		SCENE->AddScene("GameOverScene", new cGameOverScene);

		UI->Init();

		SCENE->ChangeScene("TitleScene", "None", 0.f);
	}
}

void cLoadScene::Render()
{
	IMAGE->Render(m_bg->m_text, VEC2(0, 0));
}

void cLoadScene::Release()
{
}