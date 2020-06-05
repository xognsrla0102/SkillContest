#include "DXUT.h"
#include "cScroolMap.h"
#include "cTimer.h"
#include "cMeteor.h"
#include "cStraight.h"
#include "cRazer.h"
#include "cRadial.h"
#include "cEnemyManager.h"
#include "cStageOne.h"

cStageOne::cStageOne()
{
	m_map = new cScroolMap(IMAGE->FindTexture("StageOneBG"));
	m_timePlus = new cTimer(1);
	m_createMeteor = new cTimer(0.3);
	m_createRazer = new cTimer(10);
	m_createStraight = new cTimer(1);
	m_createRadial = new cTimer(1);
	m_createRotate = new cTimer(3);
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
	GAME->Init();
	SOUND->Play("StageBGM", true);
	OBJFIND(PLAYER)->SetActive(true);
	((cPlayer*)OBJFIND(PLAYER))->Init();
	m_map->Init();

	CAMERA->m_pos = VEC2(WINSIZEX / 2 + 300, WINSIZEY / 2);

	m_gameTime = 0;
	m_isMidBoss = false;
	m_isBoss = false;

	m_patternTime = 0.f;
	m_mapPattern = rand() % m_totalPattern;
}

void cStageOne::Update()
{
	GAME->Update();

	if (m_timePlus->Update()) m_gameTime++;
	if (m_gameTime == 1000) m_isMidBoss = true;
	if (m_gameTime == 2000) m_isBoss = true;

	if (m_isMidBoss == false && m_isBoss == false) {
		m_map->Update();
		MapPattern();
	}
}

void cStageOne::Render()
{
	m_map->Render();
}

void cStageOne::Release()
{
	SOUND->Stop("StageBGM");
	((cPlayer*)OBJFIND(PLAYER))->Release();
	OBJFIND(PLAYER)->SetActive(false);
	((cBulletManager*)OBJFIND(BULLET))->Reset();
	((cEnemyManager*)OBJFIND(ENEMY))->Release();
	EFFECT->Reset();
	m_map->Release();
}

void cStageOne::DelayPattern()
{
	//Boss 땐 지형 없음
	if (m_patternTime > 10.f) {
		m_patternTime = 0.f;
		m_mapPattern = rand() % m_totalPattern;
	}
}

void cStageOne::MapPattern()
{
	m_patternTime += D_TIME;
		
	if (m_mapPattern == 4) m_createMeteor->m_delay = 1.f;
	else m_createMeteor->m_delay = 0.3;

	m_mapPattern = 4;

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
}

void cStageOne::MapPattern1()
{
	if (m_patternTime > 30.f) {
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
				new cMeteor(key, VEC2(GXY(50, -50)), VEC2(1, 1), 60 * rand() % 6, 200.f)
			);

			sprintf(key, "EnemyMeteor%dIMG", rand() % 3);
			((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor().push_back(
				new cMeteor(key, VEC2(GXY(GAMESIZEX - 50, -50)), VEC2(1, 1), 60 * rand() % 6, 200.f)
			);
		}

		//맵의 패턴이 좌우 운석 직선 일 때
		//돌아가는 적과, 레이저 적
		if (m_createRazer->Update()) {
			((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
				new cRazer(VEC2(GXY(120 + rand() % (GAMESIZEX - 240), -200)))
			);
		}
		if (m_createStraight->Update()) {
			((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
				new cStraight(VEC2(GXY(120 + rand() % (GAMESIZEX - 240), -200)))
			);
		}
	}
}

void cStageOne::MapPattern2()
{
	static int cnt = 0, dir = 1;

	if (m_patternTime > 5.f) {
		m_createRotate->m_start = 0.f;
		m_createStraight->m_start = 0.f;

		m_patternTime = 0.f;
		m_mapPattern = rand() % m_totalPattern;
		cnt = 0;
		dir = 1;
	}
	else {
		if (m_createMeteor->Update()) {
			char key[256];
			sprintf(key, "EnemyMeteor%dIMG", rand() % 3);
			((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor().push_back(
				new cMeteor(key, VEC2(GXY(10 + cnt * 30, -50)), VEC2(1, 1), 60 * rand() % 6, 200.f)
			);

			sprintf(key, "EnemyMeteor%dIMG", rand() % 3);
			((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor().push_back(
				new cMeteor(key, VEC2(GXY(GAMESIZEX - 50, -50)), VEC2(1, 1), 60 * rand() % 6, 200.f)
			);
			cnt += dir;
		}

		if (m_createStraight->Update()) {
			((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
				new cStraight(VEC2(GXY(120 + rand() % (GAMESIZEX - 240), -200)))
			);
		}
	}

	if (dir == -1 && cnt < 0) dir = 1;
	else if (dir == 1 && cnt > 6) dir = -1;
}

void cStageOne::MapPattern3()
{
	static int cnt = 0, dir = 1;

	if (m_patternTime > 5.f) {
		m_createRotate->m_start = 0.f;
		m_createStraight->m_start = 0.f;

		m_patternTime = 0.f;
		m_mapPattern = rand() % m_totalPattern;
		cnt = 0;
		dir = 1;
	}
	else {
		if (m_createMeteor->Update()) {
			char key[256];
			sprintf(key, "EnemyMeteor%dIMG", rand() % 3);
			((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor().push_back(
				new cMeteor(key, VEC2(GXY(50, -50)), VEC2(1, 1), 60 * rand() % 6, 200.f)
			);

			sprintf(key, "EnemyMeteor%dIMG", rand() % 3);
			((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor().push_back(
				new cMeteor(key, VEC2(GXY(GAMESIZEX - 50 - cnt * 30, -50)), VEC2(1, 1), 60 * rand() % 6, 200.f)
			);
			cnt += dir;
		}

		if (m_createStraight->Update()) {
			((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
				new cStraight(VEC2(GXY(120 + rand() % (GAMESIZEX - 240), -200)))
			);
		}
	}

	if (dir == -1 && cnt < 0) dir = 1;
	else if (dir == 1 && cnt > 6) dir = -1;
}

void cStageOne::MapPattern4()
{
	if (m_patternTime > 30.f) {
		m_createRadial->m_start = 0.f;
		m_createRazer->m_start = 0.f;

		m_patternTime = 0.f;
		m_mapPattern = rand() % m_totalPattern;
	}
	else {
		if (m_createMeteor->Update()) {
			char key[256];
			sprintf(key, "EnemyMeteor%dIMG", rand() % 3);
			((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor().push_back(
				new cMeteor(key, VEC2(GXY(rand() % GAMESIZEX, -50)), VEC2(1, 1), 60 * rand() % 6, 200.f)
			);
		}

		if (m_createRazer->Update()) {
			((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
				new cRazer(VEC2(GXY(120 + rand() % (GAMESIZEX - 240), -200)))
			);
		}

		if (m_createRadial->Update() && ((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().size() < 2) {
			((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
				new cRadial(VEC2(GXY(20, GAMESIZEY + 50)))
			);

			((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy().push_back(
				new cRadial(VEC2(GXY(GAMESIZEX - 20, -50)))
			);

		}
	}
}
