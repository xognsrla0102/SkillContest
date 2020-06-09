#include "DXUT.h"
#include "cIngameUI.h"
#include "cScroolMap.h"
#include "cTimer.h"
#include "cMeteor.h"
#include "cStraight.h"
#include "cRazer.h"
#include "cRadial.h"
#include "cRotate.h"
#include "cMidBoss.h"
#include "cBoss.h"
#include "cEnemyManager.h"
#include "cStageOne.h"

cStageOne::cStageOne()
{
	m_map = new cScroolMap(IMAGE->FindTexture("StageOneBG"));
	m_timePlus = new cTimer(1);
	m_createMeteor = new cTimer(0.3);
	m_createRazer = new cTimer(5);
	m_createStraight = new cTimer(1);
	m_createRadial = new cTimer(1);
	m_createRotate = new cTimer(1.5);
}

cStageOne::~cStageOne()
{
	Release();
	SAFE_DELETE(m_map);
	SAFE_DELETE(m_timePlus);
	SAFE_DELETE(m_createMeteor);
	SAFE_DELETE(m_createRazer);
	SAFE_DELETE(m_createStraight);
	SAFE_DELETE(m_createRadial);
	SAFE_DELETE(m_createRotate);
}

void cStageOne::Init()
{
	if (GAME->m_nowStage == 1) GAME->Init();
	else GAME->StageInit();

	SOUND->Play("StageBGM", true);

	m_nowBGM = "StageBGM";

	((cIngameUI*)UI->FindUI("IngameSceneUI"))->Init();

	OBJFIND(PLAYER)->SetActive(true);
	((cPlayer*)OBJFIND(PLAYER))->Init();
	m_map->Init();
	
	CAMERA->m_pos = VEC2(WINSIZEX / 2 + 300, WINSIZEY / 2);
	
	m_gameTime = 0;
	
	m_patternTime = 0.f;
	m_mapPattern = 0;
	
	m_createRazer->m_delay = 5.f / GAME->m_nowStage;
	m_createStraight->m_delay = 1.f / GAME->m_nowStage;
}

void cStageOne::Update()
{
	GAME->Update();
	
	if (m_timePlus->Update()) {
		m_gameTime++;
	
		//미드보스 끝나기 10초전
		if (
			(GAME->m_isMidBoss && (m_createMidBossTime + 40 <= m_gameTime && m_gameTime <= m_createMidBossTime + 50)) ||
			(GAME->m_isBoss && (m_createBossTime + 50 <= m_gameTime && m_gameTime <= m_createBossTime + 60))
		) {
			SOUND->Copy("WarningSND");
			SOUND->Copy("WarningSND");
			SOUND->Copy("WarningSND");
		}
	
		if (m_gameTime == 50) {
			((cItemManager*)OBJFIND(ITEM))->m_items.push_back(
				new cItem("ItemHpIMG", GXY(GAMESIZEX / 2, -100), GXY(GAMESIZEX / 2, -100))
			);
		}
	
		if (m_gameTime == m_createMidBossTime) {
			((cItemManager*)OBJFIND(ITEM))->m_items.push_back(
				new cItem("ItemHpIMG", GXY(GAMESIZEX / 2, -100), GXY(rand() % (GAMESIZEX / 2), -100))
			);

			((cItemManager*)OBJFIND(ITEM))->m_items.push_back(
				new cItem("ItemSkillTimeIMG", GXY(GAMESIZEX / 2, -100), GXY(GAMESIZEX / 2 + rand() % (GAMESIZEX / 2), -100))
			);

			GAME->m_isMidBoss = true;
			SOUND->Stop(m_nowBGM);
			m_nowBGM = "MidBossBGM";
			SOUND->Play(m_nowBGM, true);
	
			((cEnemyManager*)OBJFIND(ENEMY))->m_mBoss = new cMidBoss;
			m_patternTime = 999.f;
		}
	
		//중간보스 싸움시간 50초
		if (m_gameTime == m_createMidBossTime + 50) {
			((cItemManager*)OBJFIND(ITEM))->m_items.push_back(
				new cItem("ItemHpIMG", GXY(GAMESIZEX / 2, -100), GXY(GAMESIZEX / 2, -100))
			);
			if (GAME->m_isMidBoss) {
				((cEnemyManager*)OBJFIND(ENEMY))->m_mBoss->SetLive(false);
			}
		}
	
		if (m_gameTime == m_createBossTime) {
			((cItemManager*)OBJFIND(ITEM))->m_items.push_back(
				new cItem("ItemHpIMG", GXY(GAMESIZEX / 2, -100), GXY(GAMESIZEX / 2, -100))
			);
			GAME->m_isBoss = true;
			SOUND->Stop(m_nowBGM);
			m_nowBGM = "LastBossBGM";
			SOUND->Play(m_nowBGM, true);

			((cEnemyManager*)OBJFIND(ENEMY))->m_boss = new cBoss;
			m_patternTime = 999.f;
		}
	
		//보스 싸움시간 60초
		if (m_gameTime == m_createBossTime + 60) {
			if (GAME->m_isBoss) {
				((cEnemyManager*)OBJFIND(ENEMY))->m_boss->SetLive(false);
				SCENE->ChangeScene("ResultScene", "Fade", 3.f);
			}
		}
	}

	MapPattern();
	if (GAME->m_isMidBoss == false && GAME->m_isBoss == false) {
		m_map->Update();
	}
}

void cStageOne::Render()
{
	if (KEYDOWN(VK_HOME))
		m_gameTime = m_createBossTime - 2;
	if (KEYDOWN(VK_END))
		m_gameTime = m_createMidBossTime - 2;

	m_map->Render();
}

void cStageOne::Release()
{
	SOUND->Stop(m_nowBGM);
	if (GAME->m_isBoss)			GAME->m_isBoss = false;
	else if (GAME->m_isMidBoss) GAME->m_isMidBoss = false;

	m_map->Release();

	OBJFIND(PLAYER)->SetActive(false);
	((cPlayer*)OBJFIND(PLAYER))->Release();
	((cBulletManager*)OBJFIND(BULLET))->Reset();
	((cEnemyManager*)OBJFIND(ENEMY))->Release();
	((cItemManager*)OBJFIND(ITEM))->Release();
	FONT->Release();
	EFFECT->Reset();
}

void cStageOne::DelayPattern()
{
	//Boss 땐 지형 없음
	if (GAME->m_isBoss || GAME->m_isMidBoss) return;
	
	if (m_patternTime > 5.f) {
		m_patternTime = 0.f;
		m_mapPattern = 1 + rand() % (m_totalPattern - 1);
	}
}

void cStageOne::MapPattern()
{
	m_patternTime += D_TIME;
		
	if (m_mapPattern == 4) m_createMeteor->m_delay = 1.f;
	else m_createMeteor->m_delay = 0.3;
	
	switch (m_mapPattern) {
	case 0:
		DelayPattern();
		break;
	case 1:
		MapPattern1();
		break;
	case 2:
		MapPattern2();
		break;
	case 3:
		MapPattern3();
		break;
	case 4:
		MapPattern4();
		break;
	}
	
	if (GAME->m_isBoss || GAME->m_isMidBoss) {
		if (m_mapPattern != 0.f) {
			m_mapPattern = 0.f;
		}
	}
}

void cStageOne::MapPattern1()
{
	if (m_patternTime > 10.f) {
		m_patternTime = 0.f;
		m_mapPattern = rand() % m_totalPattern;

		m_createRazer->m_start = 0.f;
		m_createStraight->m_start = 0.f;
	}
	else {
		if (m_createMeteor->Update()) {
			char key[256];
			sprintf(key, "EnemyMeteor%dIMG", rand() % 3);
			((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor().push_back(
				new cMeteor(key, GXY(10, -50), VEC2(1, 1), 60 * rand() % 6, 200.f)
			);

			sprintf(key, "EnemyMeteor%dIMG", rand() % 3);
			((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor().push_back(
				new cMeteor(key, GXY(GAMESIZEX - 10, -50), VEC2(1, 1), 60 * rand() % 6, 200.f)
			);
		}

		if (m_createRazer->Update()) {
			((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
				new cRazer(GXY(120 + rand() % (GAMESIZEX - 240), -200))
			);
		}
		if (m_createStraight->Update()) {
			((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
				new cStraight(GXY(120 + rand() % (GAMESIZEX - 240), -200))
			);
		}
	}
}

void cStageOne::MapPattern2()
{
	static int cnt = 0, dir = 1;

	if (m_patternTime > 10.f) {
		m_createRotate->m_start = 0.f;
		m_createStraight->m_start = 0.f;

		m_patternTime = 0.f;
		m_mapPattern = rand() % m_totalPattern;

		((cBulletManager*)OBJFIND(BULLET))->Reset();

		cnt = 0;
		dir = 1;
	}
	else {
		if (m_createMeteor->Update()) {
			char key[256];
			sprintf(key, "EnemyMeteor%dIMG", rand() % 3);
			((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor().push_back(
				new cMeteor(key, GXY(10 + cnt * 30, -50), VEC2(1, 1), 60 * rand() % 6, 200.f)
			);

			sprintf(key, "EnemyMeteor%dIMG", rand() % 3);
			((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor().push_back(
				new cMeteor(key, GXY(GAMESIZEX - 10, -50), VEC2(1, 1), 60 * rand() % 6, 200.f)
			);
			cnt += dir;
		}

		if (m_createStraight->Update()) {
			((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
				new cStraight(GXY(120 + rand() % (GAMESIZEX - 240), -200))
			);
		}

		if (m_createRotate->Update()) {
			auto& eBullet = ((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy();

			eBullet.push_back(new cRotate(GXY(-100, 0)));
			eBullet[eBullet.size() - 1]->m_path = new cPath(GXY(-100, 0));
			eBullet[eBullet.size() - 1]->m_path->AddCurve(GXY(-100, 0), GXY(GAMESIZEX, 50), GXY(GAMESIZEX - 300, GAMESIZEY + 300), 300.f);

			eBullet.push_back(new cRotate(GXY(GAMESIZEX + 100, 0)));
			eBullet[eBullet.size() - 1]->m_path = new cPath(GXY(GAMESIZEX + 100, 0));
			eBullet[eBullet.size() - 1]->m_path->AddCurve(GXY(GAMESIZEX + 100, 0), GXY(0, 50), GXY(300, GAMESIZEY + 300), 300.f);
		}
	}

	if (dir == -1 && cnt < 0) dir = 1;
	else if (dir == 1 && cnt > 6) dir = -1;
}

void cStageOne::MapPattern3()
{
	static int cnt = 0, dir = 1;

	if (m_patternTime > 10.f) {
		m_createRotate->m_start = 0.f;
		m_createStraight->m_start = 0.f;

		m_patternTime = 0.f;
		m_mapPattern = rand() % m_totalPattern;

		((cBulletManager*)OBJFIND(BULLET))->Reset();

		cnt = 0;
		dir = 1;
	}
	else {
		if (m_createMeteor->Update()) {
			char key[256];
			sprintf(key, "EnemyMeteor%dIMG", rand() % 3);
			((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor().push_back(
				new cMeteor(key, GXY(10, -50), VEC2(1, 1), 60 * rand() % 6, 200.f)
			);

			sprintf(key, "EnemyMeteor%dIMG", rand() % 3);
			((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor().push_back(
				new cMeteor(key, GXY(GAMESIZEX - 10 - cnt * 30, -50), VEC2(1, 1), 60 * rand() % 6, 200.f)
			);
			cnt += dir;
		}

		if (m_createStraight->Update()) {
			((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
				new cStraight(GXY(120 + rand() % (GAMESIZEX - 240), -200))
			);
		}

		if (m_createRotate->Update()) {
			auto& eBullet = ((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy();

			eBullet.push_back(new cRotate(GXY(-100, 0)));
			eBullet[eBullet.size() - 1]->m_path = new cPath(GXY(-100, 0));
			eBullet[eBullet.size() - 1]->m_path->AddCurve(GXY(-100, 0), GXY(GAMESIZEX, 50), GXY(GAMESIZEX - 300, GAMESIZEY + 300), 300.f);

			eBullet.push_back(new cRotate(GXY(GAMESIZEX + 100, 0)));
			eBullet[eBullet.size() - 1]->m_path = new cPath(GXY(GAMESIZEX + 100, 0));
			eBullet[eBullet.size() - 1]->m_path->AddCurve(GXY(GAMESIZEX + 100, 0), GXY(0, 50), GXY(300, GAMESIZEY + 300), 300.f);
		}
	}

	if (dir == -1 && cnt < 0) dir = 1;
	else if (dir == 1 && cnt > 6) dir = -1;
}

void cStageOne::MapPattern4()
{
	if (m_patternTime > 15.f) {
		m_createRadial->m_start = 0.f;
		m_createRazer->m_start = 0.f;

		auto& enemy = ((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy();
		size_t size = enemy.size();
		for (size_t i = 0; i < size; ++i) {
			if (enemy[i]->GetName() == "Radial") {
				SAFE_DELETE(enemy[i]);
				enemy.erase(enemy.begin() + i);
				--i, --size;
			}
		}
		((cBulletManager*)OBJFIND(BULLET))->Reset();

		m_patternTime = 0.f;
		m_mapPattern = rand() % m_totalPattern;
	}
	else {
		if (m_createMeteor->Update()) {
			char key[256];
			sprintf(key, "EnemyMeteor%dIMG", rand() % 3);
			((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor().push_back(
				new cMeteor(key, GXY(rand() % GAMESIZEX, -50), VEC2(1, 1), 60 * rand() % 6, 200.f)
			);
		}

		if (m_createRazer->Update()) {
			((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
				new cRazer(GXY(120 + rand() % (GAMESIZEX - 240), -200))
			);
		}

		if (m_createRadial->Update() && ((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().size() < 2) {
			((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
				new cRadial(GXY(20, GAMESIZEY + 50))
			);

			((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
				new cRadial(GXY(GAMESIZEX - 20, -50))
			);

		}
	}
}
