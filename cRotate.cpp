#include "DXUT.h"
#include "cRotate.h"

cRotate::cRotate(VEC2 pos) : cEnemy()
{
	m_img = new cImage;

	m_pos = pos;

	m_size = VEC2(0.8, 0.8);

	m_hp = 10 * GAME->m_level * GAME->m_level / 2;
	m_atk = 3 * GAME->m_level;

	char str[256];
	sprintf(str, "EnemyStage%d_RotateIMG", GAME->m_nowStage);
	m_img->m_text = IMAGE->FindTexture(str);

	m_path = new cPath(pos);
	m_path->AddPoint(VEC2(pos.x, GY(50)), 0.05, 0);
	m_path->AddPoint(VEC2(pos.x, GY(50)), 0, 3.f);

	//생성위치가 왼쪽일 경우 왼쪽으로 이동
	if (pos.x < GX(GAMESIZEX / 2))
		m_path->AddPoint(VEC2(GX(-200), pos.y), 0.03, 0);
	else
		m_path->AddPoint(VEC2(GX(GAMESIZEX + 200), pos.y), 0.03, 0);

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

	OutMapChk(200);
	if (m_isLive == false && !OutMapChk(200))
		Dead();

	if (CanFire()) Fire();
}

void cRotate::Render()
{
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true);
}

void cRotate::Dead()
{
	char str[256];
	sprintf(str, "Explosion%dIMG", 1 + rand() % 7);
	EFFECT->AddEffect(new cEffect(str, IMAGE->FindMultiTexture(str)->GetImgSize(), 0.02, m_pos, VEC2(0, 0), VEC2(0.5, 0.5), VEC2(0.3, 0.3)));
}

void cRotate::Fire()
{
}
