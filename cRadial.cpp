#include "DXUT.h"
#include "cRadial.h"

cRadial::cRadial(VEC2 pos) : cEnemy()
{
	m_img = new cImage;

	m_downSpd = (1 + rand() % 3) * 100;

	m_bulletDelay = 0.3;
	m_bulletDelay /= GAME->m_nowStage;

	m_pos = pos;
	m_size = VEC2(0.3, 0.3);

	m_hp = 2 * GAME->m_level * GAME->m_level / 2;
	m_atk = 3 * GAME->m_level;

	char str[256];
	sprintf(str, "EnemyStage%d_RadialIMG", GAME->m_nowStage);
	m_img->m_text = IMAGE->FindTexture(str);

	m_objName = "Radial";
}

cRadial::~cRadial()
{
	SAFE_DELETE(m_img);
}

void cRadial::Update()
{
	if (dir && m_pos.y > GY(GAMESIZEY)) dir = -1;
	else if (dir == -1 && m_pos.y < GY(0)) dir = 1;
	m_pos.y += m_downSpd * dir * D_TIME;

	m_bulletTime += D_TIME;
	if (CanFire() && m_bulletTime > m_bulletDelay) {
		m_bulletTime = 0.f;
		Fire();
	}

	OutMapChk(200);
}

void cRadial::Render()
{
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true);
}


void cRadial::Fire()
{
	static int cnt = 0;
	SOUND->Copy("EnemyFireSND");
	auto eBullet = (cBulletManager*)OBJFIND(BULLET);
	eBullet->N_Way_Tan("EnemyRadial", "EnemyRadialIMG", 4, 90, m_pos, VEC2(cos(D3DXToRadian(cnt)), sin(D3DXToRadian(cnt))), VEC2(1, 1), 50.f, 5.f);
	cnt += 3;
	if (cnt > 360) cnt -= 360;
}
