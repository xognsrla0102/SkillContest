#include "DXUT.h"
#include "cRazer.h"

cRazer::cRazer(VEC2 pos) : cEnemy()
{
	m_img = new cImage;

	m_pos = pos;

	m_hp = 5 * GAME->m_level * GAME->m_level;
	m_atk = 3 * GAME->m_level;

	char str[256];
	sprintf(str, "EnemyStage%d_RazerIMG", GAME->m_nowStage);
	m_img->m_text = IMAGE->FindTexture(str);

	m_path = new cPath(pos);
	m_path->AddPoint(VEC2(pos.x, GY(20)), 0.03, 0);
	m_path->AddPoint(VEC2(pos.x, GY(20)), 0, 5.f);
	//반반 확률로 왼쪽 아니면 오른쪽으로 사라짐
	if (rand() % 2)
		m_path->AddPoint(VEC2(-200, pos.y), 0.03, 0);
	else
		m_path->AddPoint(VEC2(200, pos.y), 0.03, 0);
}

cRazer::~cRazer()
{
	SAFE_DELETE(m_img);
	SAFE_DELETE(m_path);
}

void cRazer::Update()
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

	if (CanFire()) {
		//레이저 발사 구문
	}
}

void cRazer::Render()
{
	DEBUG_LOG("%.2f %.2f\n", m_pos.x, m_pos.y);
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true);
}

void cRazer::Dead()
{
}
