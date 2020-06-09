#include "DXUT.h"
#include "cBoss.h"

cBoss::cBoss()
{
	m_timePlus = new cTimer(1);
	m_img = new cImage;

	m_hp = 2000 * GAME->m_nowStage;
	m_hpMax = m_hp;
	m_atk = 8 * GAME->m_nowStage;

	char str[256];
	sprintf(str, "EnemyStage%d_BossIMG", GAME->m_nowStage);
	m_img->m_text = IMAGE->FindTexture(str);
	m_pos = GXY(GAMESIZEX / 2, -200);

	m_size = VEC2(0.5 * GAME->m_nowStage, 0.5 * GAME->m_nowStage);

	m_objName = "Boss";
}

cBoss::~cBoss()
{
	GAME->m_isNotDead = true;
	GAME->m_isBoss = false;
	SAFE_DELETE(m_timePlus);
	SAFE_DELETE(m_img);
}

void cBoss::Update()
{
	static int bulletCnt = 0;
	static int bulletCnt0 = 0;

	//보스가 플레이어 꼬라보게
	auto player = ((cPlayer*)OBJFIND(PLAYER));
	VEC2 dir = player->GetPos() - m_pos;

	//보간하면서 꼬라보게
	Lerp(m_rot, D3DXToDegree(atan2f(dir.y, dir.x)) - 90, 0.03);

	if (m_timePlus->Update()) {
		m_patternTime++;
	}

	//생성 후 30초까지는 랜덤으로 움직임
	if (m_patternTime < 30) {
		if (m_isMoveDone) {
			m_nextPos = GXY(rand() % GAMESIZEX, rand() % 150);
			m_isMoveDone = false;
		}
		else {
			Lerp(m_pos, m_nextPos, 0.03);
			if (DistPoint(m_pos, m_nextPos) < 5.f)
				m_isMoveDone = true;
		}
	}
	else if (m_patternTime == 30) {
		m_nextPos = GXY(GAMESIZEX / 2, 150);
	}
	else if (m_patternTime > 30) {
		Lerp(m_pos, m_nextPos, 0.03);
		if (DistPoint(m_pos, m_nextPos) < 1.f) {
			m_pos = GXY(GAMESIZEX / 2, 150);
			m_isMoveDone = true;
		}
	}

	m_circleTan += D_TIME;
	if (bulletCnt0 != 6 && m_circleTan > 0.1f / GAME->m_nowStage) {
		m_circleTan = 0.f;
		VEC2 dir = OBJFIND(PLAYER)->GetPos() - m_pos;
		((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan(
			"EnemyRadial", "EnemyRadialIMG", 5 - bulletCnt0, 5 + 3 * bulletCnt0, m_pos, dir, VEC2(1.5, 1.5), (100.f + 30 * bulletCnt0) * GAME->m_nowStage, 3.f
		);
		bulletCnt0++;
	}
	else if (bulletCnt0 == 6 && m_circleTan > 5.f / GAME->m_nowStage) {
		m_circleTan = 0.f;
		bulletCnt0 = 0;
	}

	static VEC2 staticDir;
	static float rot;
	static int point;

	m_straightTan += D_TIME;
	if (bulletCnt != 5 && m_straightTan > 0.02f / GAME->m_nowStage) {
		m_straightTan = 0.f;
		if (bulletCnt == 0) {
			staticDir = OBJFIND(PLAYER)->GetPos() - m_pos;
			rot = D3DXToDegree(atan2f(staticDir.y, staticDir.x));
			point = 3 + rand() % 5;
		}

		for (int i = 0; i < point; ++i) {
			float newRot = rot + i * (360.f / point);

			staticDir.x = cos(D3DXToRadian(newRot + bulletCnt * 5));
			staticDir.y = sin(D3DXToRadian(newRot + bulletCnt * 5));
			D3DXVec2Normalize(&staticDir, &staticDir);

			((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan(
				"EnemyStraight", "EnemyStraightIMG", 1, 0, m_pos, staticDir, VEC2(1.2, 1.2), 50.f, 3.f, false, true
			);
			staticDir.x = cos(D3DXToRadian(newRot - bulletCnt * 5));
			staticDir.y = sin(D3DXToRadian(newRot - bulletCnt * 5));
			D3DXVec2Normalize(&staticDir, &staticDir);

			((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan(
				"EnemyRadial", "EnemyRadialIMG", 1, 0, m_pos, staticDir, VEC2(1.2, 1.2), 50.f, 3.f, false, true
			);
		}
		bulletCnt++;
	}
	else if (bulletCnt == 5 && m_straightTan > 1.f / GAME->m_nowStage) {
		m_straightTan = 0.f;
		bulletCnt = 0;
	}
}

void cBoss::Render()
{
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true);
}

