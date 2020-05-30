#include "DXUT.h"
#include "cTimer.h"
#include "cBullet.h"
#include "cBulletManager.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	Init();

	//¸ð¼Ç ÀÌÆåÆ® °¹¼ö
	for(size_t i = 0; i < 5; i++)
		m_motionInfo.push_back(new cMotionInfo(m_pos));

	m_motionInfo[0]->m_color = D3DCOLOR_ARGB(45, 128, 128, 255);
	m_motionInfo[1]->m_color = D3DCOLOR_ARGB(90, 128, 128, 255);
	m_motionInfo[2]->m_color = D3DCOLOR_ARGB(135, 128, 128, 255);
	m_motionInfo[3]->m_color = D3DCOLOR_ARGB(180, 128, 128, 255);
	m_motionInfo[4]->m_color = D3DCOLOR_ARGB(225, 128, 128, 255);

	m_fire = new cTimer(-1);
	m_motion = new cTimer(0.02);

	m_img = new cImage;
	m_img->m_text = IMAGE->FindTexture("PlayerIdle");

	m_ani = new cAnimation(0.13, 5, true);
}

cPlayer::~cPlayer()
{
	for (auto iter : m_motionInfo)
		SAFE_DELETE(iter);

	SAFE_DELETE(m_img);
	SAFE_DELETE(m_fire);
	SAFE_DELETE(m_motion);
	SAFE_DELETE(m_ani);
}

void cPlayer::Update()
{
	if (!m_isActive) return;

	m_ani->Update();

	Move();
	ChangeWeapon();

	if (m_isBoost)
		Boost();

	if (m_status == P_IDLE)
		m_img->m_text = IMAGE->FindTexture("PlayerIdle");
	else if (m_status == P_LEFT)
		m_img->m_text = IMAGE->FindTexture("PlayerLeft", m_ani->m_nowFrame);
	else if (m_status == P_RIGHT)
		m_img->m_text = IMAGE->FindTexture("PlayerRight", m_ani->m_nowFrame);

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
	m_size = VEC2(0.8, 0.8);
	m_isBoost = false;
	m_boostTime = 0.f;
	m_boostDelay = 0.3;
}

void cPlayer::Release()
{
}

void cPlayer::ChangeWeapon()
{
	if (KEYDOWN('1')) m_nowWeapon = 0;
	else if (KEYDOWN('2')) m_nowWeapon = 1;
	else if (KEYDOWN('3')) m_nowWeapon = 2;
	else if (KEYDOWN('4')) m_nowWeapon = 3;
	else if (KEYDOWN('5')) m_nowWeapon = 4;
}

void cPlayer::Boost()
{
	m_boostTime += D_TIME;
	if (m_boostTime < m_boostDelay)
		Lerp(m_moveSpd, m_moveSpd, m_originSpd, 0.3);
	else {
		m_moveSpd = m_originSpd;
		m_boostTime = 0.f;
		m_isBoost = false;
	}
}

void cPlayer::Move()
{
	if (KEYDOWN('R') && 
		(KEYPRESS(VK_UP) || KEYPRESS(VK_DOWN) || KEYPRESS(VK_LEFT) || KEYPRESS(VK_RIGHT))
		) {
		CAMERA->SetShake(0.13, 20, 4);
		m_isBoost = true;
		m_moveSpd = m_originSpd * 5;
	}

	if (KEYPRESS(VK_LSHIFT)) m_moveSpd = m_originSpd * 0.5;
	else if(m_isBoost == false) m_moveSpd = m_originSpd;

	if (KEYPRESS(VK_UP)) {
		m_pos.y -= m_moveSpd * D_TIME;
		if (m_pos.y < 0) m_pos.y = 0;
	}
	if (KEYPRESS(VK_DOWN)) {
		m_pos.y += m_moveSpd * D_TIME;
		if (m_pos.y > 2160) m_pos.y = 2160;
	}

	if (KEYPRESS(VK_LEFT) && KEYPRESS(VK_RIGHT)) {
		if (m_status != P_IDLE) {
			m_status = P_IDLE;
			m_ani->m_nowFrame = 0;
		}
	}
	else if (KEYPRESS(VK_LEFT) || KEYPRESS(VK_RIGHT)) {
		if (KEYPRESS(VK_LEFT)) {
			if (m_status != P_LEFT) {
				m_status = P_LEFT;
				m_ani->m_nowFrame = 0;
			}
			m_pos.x -= m_moveSpd * D_TIME;
			if (m_pos.x < 0) m_pos.x = 0;
		}
		else {
			if (m_status != P_RIGHT) {
				m_status = P_RIGHT;
				m_ani->m_nowFrame = 0;
			}
			m_pos.x += m_moveSpd * D_TIME;
			if (m_pos.x > 3840) m_pos.x = 3840;
		}
	}
	else {
		if (m_status != P_IDLE) {
			m_status = P_IDLE;
			m_ani->m_nowFrame = 0;
		}
	}
}

void cPlayer::Fire()
{
	if (KEYPRESS(VK_SPACE)) {
		switch (m_nowWeapon) {
		case 0:
			SOUND->Copy("Bullet0SND");
			switch (GAME->m_level) {
			case 1:
				m_fire->m_delay = 0.5f;
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 3, 10, m_pos, VEC2(0, -1), 1000.f);
				break;
			case 2:
				m_fire->m_delay = 0.4f;
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 3, 10, m_pos, VEC2(0, -1), 1200.f);
				break;
			case 3:
				m_fire->m_delay = 0.4f;
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 5, 10, m_pos, VEC2(0, -1), 1200.f);
				break;
			case 4:
				m_fire->m_delay = 0.2f;
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 5, 10, m_pos, VEC2(0, -1), 1400.f);
				break;
			case 5:
				m_fire->m_delay = 0.1f;
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 8, 10, m_pos, VEC2(0, -1), 1400.f);
				break;
			}
			break;
		case 1:
			SOUND->Copy("Bullet1SND");
			switch (GAME->m_level) {
			case 1:
				m_fire->m_delay = 0.15f;
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet2IMG", 1, 10, m_pos, VEC2(0, -1), 1000.f);
				break;
			case 2:
				m_fire->m_delay = 0.1f;
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet2IMG", 3, 10, m_pos, VEC2(0, -1), 1000.f);
				break;
			case 3:
				m_fire->m_delay = 0.1f;
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet2IMG", 3, 20, m_pos, VEC2(0, -1), 1300.f);
				break;
			case 4:
				m_fire->m_delay = 0.08f;
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet2IMG", 5, 20, m_pos, VEC2(0, -1), 1300.f);
				break;
			case 5:
				m_fire->m_delay = 0.08f;
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet2IMG", 8, 20, m_pos, VEC2(0, -1), 1300.f);
				break;
			}
			break;
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
