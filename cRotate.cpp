#include "DXUT.h"
#include "cRotate.h"

cRotate::cRotate(VEC2 pos) : cEnemy()
{
	m_img = new cImage;

	m_pos = pos;

	m_bulletTime = 0.f;
	m_bulletDelay = 0.5 + rand() % 6 / 10.f;
	m_bulletDelay /= GAME->m_nowStage;

	m_size = VEC2(0.3, 0.3);

	m_hp = 2 * GAME->m_level * GAME->m_level / 2;
	m_atk = 3 * GAME->m_level;

	char str[256];
	sprintf(str, "EnemyStage%d_RotateIMG", GAME->m_nowStage);
	m_img->m_text = IMAGE->FindTexture(str);

	m_objName = "Rotate";
}

cRotate::~cRotate()
{
	SAFE_DELETE(m_img);
	SAFE_DELETE(m_path);
}

void cRotate::Update()
{
	cPointInfo nowPath = m_path->m_endPoint[m_path->m_nowPos];

	VEC2 dir = nowPath.m_pos - m_pos;
	D3DXVec2Normalize(&dir, &dir);
	float moveDist = D3DXVec2Length(&(dir * nowPath.m_speed * D_TIME));
	moveDist *= m_isAccelCurve ? m_accelCurve : 1;

	bool cngNextPoint = m_path->Update(m_pos, moveDist);
	if (m_path->m_isDone) {
		m_isLive = false;
		return;
	}
	if (cngNextPoint) {
		if (m_path->m_nowPos != 0) m_pos = m_path->m_endPoint[m_path->m_nowPos - 1].m_pos;
		else m_pos = m_path->m_endPoint[0].m_pos;
	}

	nowPath = m_path->m_endPoint[m_path->m_nowPos];
	if (nowPath.m_isCurve == false) Lerp(m_pos, nowPath.m_pos, nowPath.m_speed);
	else {
		VEC2 dir = nowPath.m_pos - m_pos;
		D3DXVec2Normalize(&dir, &dir);
		if (m_isAccelCurve == TRUE) {
			if (m_accelCurve < 1.f) m_accelCurve += D_TIME / m_divDelta;
			else m_accelCurve = 1.f;
			m_pos += dir * nowPath.m_speed * D_TIME * m_accelCurve;
		}
		else {
			m_pos += dir * nowPath.m_speed * D_TIME;
		}
	}


	m_bulletTime += D_TIME;
	if (CanFire() && m_bulletTime > m_bulletDelay) {
		m_bulletTime = 0.f;
		Fire();
	}

	OutMapChk(200);

	m_rot+=5;
	if (m_rot > 360) m_rot -= 360;
}

void cRotate::Render()
{
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true);
}

void cRotate::Fire()
{
	static int cnt = 0;
	SOUND->Copy("EnemyFireSND");
	auto eBullet = (cBulletManager*)OBJFIND(BULLET);
	eBullet->N_Way_Tan("EnemyRotate", "EnemyRadialIMG", 4, 90, m_pos, VEC2(cos(D3DXToRadian(cnt)), sin(D3DXToRadian(cnt))), VEC2(1, 1), 50.f, 5.f);
	cnt += 5;
	if (cnt > 360) cnt -= 360;
}
