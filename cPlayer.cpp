#include "DXUT.h"
#include "cTimer.h"
#include "cBullet.h"
#include "cBulletManager.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	Init();

	//모션 이펙트 갯수
	for(size_t i = 0; i < 5; i++)
		m_motionInfo.push_back(new cMotionInfo(m_pos));

	m_motionInfo[0]->m_color = D3DCOLOR_ARGB(45, 128, 128, 255);
	m_motionInfo[1]->m_color = D3DCOLOR_ARGB(90, 128, 128, 255);
	m_motionInfo[2]->m_color = D3DCOLOR_ARGB(135, 128, 128, 255);
	m_motionInfo[3]->m_color = D3DCOLOR_ARGB(180, 128, 128, 255);
	m_motionInfo[4]->m_color = D3DCOLOR_ARGB(225, 128, 128, 255);

	m_fire = new cTimer(-1);
	m_motion = new cTimer(0.02);
	m_boost = new cTimer(3);

	m_img = new cImage;
	m_img->m_text = IMAGE->FindTexture("PlayerIMG");
}

cPlayer::~cPlayer()
{
	for (auto iter : m_motionInfo)
		SAFE_DELETE(iter);

	SAFE_DELETE(m_img);
	SAFE_DELETE(m_fire);
	SAFE_DELETE(m_motion);
	SAFE_DELETE(m_boost);
}

void cPlayer::Update()
{
	if (!m_isActive) return;

	DEBUG_LOG("%.2f\n", m_fire->m_delay);

	if (KEYDOWN('R')) {
		DEBUG_LOG("레벨업!\n");
		if(GAME->m_level < 5)
			GAME->m_level++;
	}
	if (KEYDOWN('C')) {
		DEBUG_LOG("타입 변경!\n");
		m_isWayTan = !m_isWayTan;
	}

	Move();

	if (m_motion->Update())
		MotionBlur();

	if (m_canFire == false) {
		if (m_fire->Update()) {
			if (!m_canFire)
				m_canFire = true;
		}
	}
	else {
		Fire();
	}
}

void cPlayer::Render()
{
	if (!m_isActive) return;

	for (auto iter : m_motionInfo)
		IMAGE->Render(m_img->m_text, iter->m_motionPos, m_size, m_rot, true, iter->m_color);

	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true, m_img->m_color);
}


void cPlayer::Init()
{
	GAME->m_level = 1;
	m_originSpd = m_moveSpd = 500.f;
	m_pos = VEC2(WINSIZEX / 2, WINSIZEY - 100);
	m_size = VEC2(0.3, 0.3);
}

void cPlayer::Release()
{
}

void cPlayer::Move()
{
	if (KEYPRESS(VK_LSHIFT)) m_moveSpd = m_originSpd * 0.5;
	else m_moveSpd = m_originSpd;

	//if (m_motion->Update()) {
	//	
	//}

	if (KEYPRESS(VK_UP)) {
		m_pos.y -= m_moveSpd * D_TIME;
	}
	if (KEYPRESS(VK_DOWN)) {
		m_pos.y += m_moveSpd * D_TIME;
	}
	if (KEYPRESS(VK_LEFT)) {
		m_pos.x -= m_moveSpd * D_TIME;
	}
	if (KEYPRESS(VK_RIGHT)) {
		m_pos.x += m_moveSpd * D_TIME;
	}
}

void cPlayer::Fire()
{
	if (KEYPRESS(VK_SPACE)) {
		SOUND->Copy("Bullet1SND");

		if (m_isWayTan) {
			switch (GAME->m_level) {
			case 1:
				m_bulletSpd = 1000.f;
				m_fire->m_delay = 0.5f;
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 3, 10, m_pos, VEC2(0, -1), m_bulletSpd);
				break;
			case 2:
				m_bulletSpd = 1200.f;
				m_fire->m_delay = 0.4f;
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 3, 10, m_pos, VEC2(0, -1), m_bulletSpd);
				break;
			case 3:
				m_bulletSpd = 1200.f;
				m_fire->m_delay = 0.4f;
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 5, 10, m_pos, VEC2(0, -1), m_bulletSpd);
				break;
			case 4:
				m_bulletSpd = 1400.f;
				m_fire->m_delay = 0.2f;
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 5, 10, m_pos, VEC2(0, -1), m_bulletSpd);
				break;
			case 5:
				m_bulletSpd = 1400.f;
				m_fire->m_delay = 0.1f;
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 8, 10, m_pos, VEC2(0, -1), m_bulletSpd);
				break;
			}
		}
		else {
			switch (GAME->m_level) {
			case 1:
				m_bulletSpd = 1000.f;
				m_fire->m_delay = 0.15f;
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet2IMG", 1, 10, m_pos, VEC2(0, -1), m_bulletSpd);
				break;
			case 2:
				m_bulletSpd = 1000.f;
				m_fire->m_delay = 0.1f;
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet2IMG", 3, 10, m_pos, VEC2(0, -1), m_bulletSpd);
				break;
			case 3:
				m_bulletSpd = 1300.f;
				m_fire->m_delay = 0.1f;
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet2IMG", 3, 20, m_pos, VEC2(0, -1), m_bulletSpd);
				break;
			case 4:
				m_bulletSpd = 1300.f;
				m_fire->m_delay = 0.08f;
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet2IMG", 5, 20, m_pos, VEC2(0, -1), m_bulletSpd);
				break;
			case 5:
				m_bulletSpd = 1300.f;
				m_fire->m_delay = 0.08f;
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet2IMG", 8, 20, m_pos, VEC2(0, -1), m_bulletSpd);
				break;
			}
		}
		m_canFire = false;
	}
}

void cPlayer::MotionBlur()
{
	for (int i = 0; i < m_motionInfo.size() - 1; ++i)
		m_motionInfo[i]->m_motionPos = m_motionInfo[i + 1]->m_motionPos;

	m_motionInfo[m_motionInfo.size() - 1]->m_motionPos = m_pos;
}
