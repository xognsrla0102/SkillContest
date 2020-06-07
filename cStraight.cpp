#include "DXUT.h"
#include "cStraight.h"

cStraight::cStraight(VEC2 pos) : cEnemy()
{
	m_img = new cImage;

	m_downSpd = (1 + rand() % 3) * 100;

	m_bulletDelay = 0.8 + rand() % 30 / 10.f;
	m_bulletDelay /= GAME->m_nowStage;

	m_pos = pos;
	m_size = VEC2(0.3, 0.3);

	m_hp = 2 * GAME->m_level * GAME->m_level / 2;
	m_atk = 3 * GAME->m_level;

	char str[256];
	sprintf(str, "EnemyStage%d_StraightIMG", GAME->m_nowStage);
	m_img->m_text = IMAGE->FindTexture(str);

	m_objName = "Straight";
}

cStraight::~cStraight()
{
	SAFE_DELETE(m_img);
}

void cStraight::Update()
{
	m_pos.y += m_downSpd * D_TIME;

	m_bulletTime += D_TIME;
	if (CanFire() && m_bulletTime > m_bulletDelay) {
		m_bulletTime = 0.f;
		Fire();
	}

	OutMapChk(200);
}

void cStraight::Render()
{
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true);
}

void cStraight::Fire()
{
	SOUND->Copy("EnemyFireSND");
	auto eBullet = (cBulletManager*)OBJFIND(BULLET);
	eBullet->N_Way_Tan("EnemyStraight", "EnemyStraightIMG", 3, 10, VEC2(m_pos.x, m_pos.y + 20), VEC2(0, 1), VEC2(1.5, 1.5), 70.f, 5.f, false, false, false, true);
}
