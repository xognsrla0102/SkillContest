#include "DXUT.h"
#include "cScroolMap.h"
#include "cTimer.h"
#include "cMeteor.h"
#include "cEnemyManager.h"
#include "cStageOne.h"

cStageOne::cStageOne()
{
	m_map = new cScroolMap(IMAGE->FindTexture("StageOneBG"));
	m_timePlus = new cTimer(1);
	m_createMeteor = new cTimer(0.3);
}

cStageOne::~cStageOne()
{
	Release();

	SAFE_DELETE(m_map);
	SAFE_DELETE(m_timePlus);
	SAFE_DELETE(m_createMeteor);
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
	m_mapPattern = 0;
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
	OBJFIND(PLAYER)->SetActive(false);
	((cBulletManager*)OBJFIND(BULLET))->Reset();
	((cEnemyManager*)OBJFIND(ENEMY))->Release();
	EFFECT->Reset();
	m_map->Release();
}

void cStageOne::DelayPattern()
{
	if (m_patternTime > 3.f) {
		m_patternTime = 0.f;
		//한 번 더 딜레이 걸리면 맵 생성이 너무 늦을 것 같아서 빼버림
		m_mapPattern = 1 + rand() % (m_totalPattern - 1);
	}
}

void cStageOne::MapPattern()
{
	m_patternTime += D_TIME;

	if (m_mapPattern == 4) m_createMeteor->m_delay = 0.5;
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
}

void cStageOne::MapPattern1()
{
	if (m_patternTime > 5.f) {
		m_patternTime = 0.f;
		m_mapPattern = rand() % m_totalPattern;
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
	}
}

void cStageOne::MapPattern2()
{
	static int cnt = 0, dir = 1;

	if (m_patternTime > 5.f) {
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
	}

	if (dir == -1 && cnt < 0) dir = 1;
	else if (dir == 1 && cnt > 6) dir = -1;
}

void cStageOne::MapPattern3()
{
	static int cnt = 0, dir = 1;

	if (m_patternTime > 5.f) {
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
	}

	if (dir == -1 && cnt < 0) dir = 1;
	else if (dir == 1 && cnt > 6) dir = -1;
}

void cStageOne::MapPattern4()
{
	if (m_patternTime > 5.f) {
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
	}
}
