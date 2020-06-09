#include "DXUT.h"
#include "cMidBoss.h"

cMidBoss::cMidBoss()
{
	m_timePlus = new cTimer(1);
	m_img = new cImage;

	m_hp = 1200 * GAME->m_nowStage;
	m_hpMax = m_hp;
	m_atk = 5 * GAME->m_nowStage;

	char str[256];
	sprintf(str, "EnemyStage%d_MidBossIMG", GAME->m_nowStage);
	m_img->m_text = IMAGE->FindTexture(str);
	m_pos = GXY(GAMESIZEX / 2, -200);

	m_size = VEC2(0.25 * GAME->m_nowStage, 0.25  * GAME->m_nowStage);

	m_objName = "MidBoss";
}

cMidBoss::~cMidBoss()
{
	GAME->m_isMidBoss = false;
	SAFE_DELETE(m_timePlus);
	SAFE_DELETE(m_img);
}

void cMidBoss::Update()
{
	//보스가 플레이어 꼬라보게
	auto player = ((cPlayer*)OBJFIND(PLAYER));
	VEC2 dir = player->GetPos() - m_pos;

	//보간하면서 꼬라보게
	Lerp(m_rot, D3DXToDegree(atan2f(dir.y, dir.x)) - 90, 0.03);

	if (m_timePlus->Update()) {
		m_patternTime++;
	}

	//생성 후 1분까지는 랜덤으로 움직임
	if (m_patternTime < 60) {
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

	m_circleTan += D_TIME;
	if (m_circleTan > 0.3 / GAME->m_nowStage) {
		m_circleTan = 0.f;
		VEC2 newDir;
		for (int i = 0; i < 6; ++i) {
			newDir.x = cos(D3DXToRadian(m_dirRot + i * 60));
			newDir.y = sin(D3DXToRadian(m_dirRot + i * 60));
			((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan(
				"EnemyRadial", "EnemyRadialIMG", 2, 20, m_pos, newDir, VEC2(1.5, 1.5), 200.f, 3.f
			);
		}
		m_dirRot -= 10;
		if (m_dirRot < 0) m_dirRot += 360;
	}

	m_straightTan += D_TIME;
	if (m_straightTan > 1.f / GAME->m_nowStage) {
		m_straightTan = 0.f;
		VEC2 dir = OBJFIND(PLAYER)->GetPos() - m_pos;
		D3DXVec2Normalize(&dir, &dir);
		((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan(
			"EnemyStraight", "EnemyStraightIMG", 2, 20, m_pos, dir, VEC2(1.5, 1.5), 200.f, 3.f
		);
	}
}

void cMidBoss::Render()
{
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true);
}

