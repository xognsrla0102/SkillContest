#include "DXUT.h"
#include "cRazer.h"

cRazer::cRazer(VEC2 pos) : cEnemy()
{
	m_img = new cImage;

	//레이저 애니메이션 정보
	m_chargeEffect = new cAnimation(0.03, 24, true);

	m_pos = pos;

	m_hp = 10 * GAME->m_level * GAME->m_level / 2;
	m_atk = 3 * GAME->m_level;

	char str[256];
	sprintf(str, "EnemyStage%d_RazerIMG", GAME->m_nowStage);
	m_img->m_text = IMAGE->FindTexture(str);

	m_path = new cPath(pos);
	m_path->AddPoint(VEC2(pos.x, GY(50)), 0.05, 0);
	m_path->AddPoint(VEC2(pos.x, GY(50)), 0, 3.f);
	
	//생성위치가 왼쪽일 경우 왼쪽으로 이동
	if (pos.x < GX(GAMESIZEX / 2))
		m_path->AddPoint(VEC2(GX(-200), pos.y), 0.03, 0);
	else
		m_path->AddPoint(VEC2(GX(GAMESIZEX + 200), pos.y), 0.03, 0);

	m_objName = "Razer";
}

cRazer::~cRazer()
{
	SAFE_DELETE(m_img);
	SAFE_DELETE(m_path);
	SAFE_DELETE(m_chargeEffect);
}

void cRazer::Update()
{
	cPointInfo nowPath = m_path->m_endPoint[m_path->m_nowPos];

	//가만히 있기 시작할 때 레이저 로드를 해줘야함
	if (nowPath.m_delay != 0) {
		if (m_isChargeTime != true) {
			SOUND->Copy("RazerChargeSND");
			m_isChargeTime = true;
		}
	}
	//다른 상태일 땐 레이저 취소
	else m_isChargeTime = false;

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

	if (CanFire() && m_isChargeTime) {
		Fire();
	}
}

void cRazer::Render()
{
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true);
	if(m_isChargeTime)
		IMAGE->Render(IMAGE->FindTexture("ChargeRazerIMG", m_chargeEffect->m_nowFrame), VEC2(m_pos.x, m_pos.y + 50), VEC2(3, 3), 0.f, true);
}

void cRazer::Dead()
{
	char str[256];
	sprintf(str, "Explosion%dIMG", 1 + rand() % 7);
	EFFECT->AddEffect(new cEffect(str, IMAGE->FindMultiTexture(str)->GetImgSize(), 0.02, m_pos, VEC2(0, 0), VEC2(0.5, 0.5), VEC2(0.3, 0.3)));
}

void cRazer::Fire()
{
	m_chargeEffect->Update();

	if (m_chargeEffect->m_nowFrame == m_chargeEffect->m_endFrame - 2) {
		CAMERA->SetShake(0.1, 5, 5);
		SOUND->Copy("RazerFireSND");
	}

	if (m_chargeEffect->m_nowFrame == m_chargeEffect->m_endFrame - 1) {
		auto& eBullet = ((cBulletManager*)OBJFIND(BULLET))->GetEnemyBullets();
		eBullet.push_back(
			new cBullet("EnemyRazerIMG", VEC2(m_pos.x, m_pos.y + 300), VEC2(0, 1), 0.f, 600.f, VEC2(3, 30))
		);
		eBullet[eBullet.size() - 1]->SetName("EnemyRazer");
		eBullet[eBullet.size() - 1]->m_atk = m_atk;
	}
}
