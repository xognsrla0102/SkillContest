#include "DXUT.h"
#include "cTimer.h"
#include "cEnemy.h"
#include "cBullet.h"
#include "cBulletManager.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	Init();

	m_fire = new cTimer(m_fireDelay[m_nowWeapon]);
	m_boostCool = new cTimer(1);
	m_motion = new cTimer(0.02);
	m_img = new cImage;
	m_boostBar = new cImage;
	m_boostBar->m_text = IMAGE->FindTexture("IngameSkillUI");
	m_ani = new cAnimation(0.13, 5, true);

	m_objName = "Player";
}

cPlayer::~cPlayer()
{
	for (auto iter : m_motionInfo)
		SAFE_DELETE(iter);

	SAFE_DELETE(m_img);
	SAFE_DELETE(m_fire);
	SAFE_DELETE(m_motion);
	SAFE_DELETE(m_ani);
	SAFE_DELETE(m_boostCool);
	SAFE_DELETE(m_boostBar);
}

void cPlayer::Update()
{
	if (!m_isActive) return;

	m_ani->Update();

	Move();
	ChangeWeapon();

	if (m_isBoostCool) {
		if (m_boostCool->Update())
			m_isBoostCool = false;
	}

	if (m_motion->Update()) MotionBlur();
	if (m_isBoost) Boost();

	if (m_status == P_IDLE)
		m_img->m_text = IMAGE->FindTexture("PlayerIdle");
	else if (m_status == P_LEFT)
		m_img->m_text = IMAGE->FindTexture("PlayerLeft", m_ani->m_nowFrame);
	else if (m_status == P_RIGHT)
		m_img->m_text = IMAGE->FindTexture("PlayerRight", m_ani->m_nowFrame);

	if (m_canFire == false) {
		if (m_fire->Update()) {
			if (!m_canFire) m_canFire = true;
		}
	}
	else {
		Fire();
	}

	if (GetActive() == false) Dead();
}

void cPlayer::Render()
{ 
	if (!m_isActive) return;

	if (m_isBoostCool) {
		RECT rt = {
			0,
			0,
			m_boostCool->m_start / m_boostCool->m_delay * m_boostBar->m_text->m_info.Width,
			m_boostBar->m_text->m_info.Height,
		};
		IMAGE->CropRender(m_boostBar->m_text, VEC2(m_pos.x, m_pos.y + 40), VEC2(0.4, 0.4), rt, true);
	}

	if (m_isBoost) {
		for (auto iter : m_motionInfo)
			IMAGE->Render(m_img->m_text, iter->m_motionPos, m_size, m_rot, true, iter->m_color);
	}
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true, m_img->m_color);
}

void cPlayer::OnCollision(cObject* other)
{
	if (AABB(GetObjCollider(), other->GetObjCollider())) {
		if (other->GetName() == "Meteor") {
			m_hp -= ((cEnemy*)other)->m_atk;
		}
	}

	if (m_hp <= 0) SetActive(false);
}


void cPlayer::Init()
{
	GAME->m_level = 1;

	m_originSpd = m_moveSpd = 500.f;
	m_boostTime = 0.f;
	m_boostDelay = 0.3;

	m_isBoostCool = false;
	m_canFire = false;

	m_pos = GXY(GAMESIZEX / 2, GAMESIZEY - 80);
	m_size = VEC2(0.8, 0.8);

	m_nowWeapon = 0;

	//초기 무기 딜레이
	m_fireDelay[0] = 1;
	m_fireDelay[1] = 0.2;

	//초기 무기 공격력
	m_atk[0] = 1;
	m_atk[1] = 3;

	m_status = P_IDLE;
	m_isQ = false;
	m_isW = false;
	m_isBoost = false;

	m_hp = 100;
	m_hpMax = 100;

	//모션 이펙트 갯수
	for (size_t i = 0; i < 5; i++)
		m_motionInfo.push_back(new cMotionInfo(m_pos));

	m_motionInfo[0]->m_color = D3DCOLOR_ARGB(45, 128, 128, 255);
	m_motionInfo[1]->m_color = D3DCOLOR_ARGB(90, 128, 128, 255);
	m_motionInfo[2]->m_color = D3DCOLOR_ARGB(135, 128, 128, 255);
	m_motionInfo[3]->m_color = D3DCOLOR_ARGB(180, 128, 128, 255);
	m_motionInfo[4]->m_color = D3DCOLOR_ARGB(225, 128, 128, 255);
}

void cPlayer::Release()
{
	for (auto iter : m_motionInfo)
		SAFE_DELETE(iter);
	m_motionInfo.clear();
}

void cPlayer::Dead()
{
	CAMERA->SetShake(0.1, 10, 10);

	//죽는 모션 후
	//게임 오버씬으로 이동
}

void cPlayer::ChangeWeapon()
{
	if		(KEYDOWN('1')) m_nowWeapon = 0;
	else if (KEYDOWN('2')) m_nowWeapon = 1;
	else if (KEYDOWN('3')) m_nowWeapon = 2;
	else if (KEYDOWN('4')) m_nowWeapon = 3;
	else if (KEYDOWN('5')) m_nowWeapon = 4;

	for (int i = '1'; i <= '5'; ++i) {
		if (KEYDOWN(i)) {
			m_fire->m_start = 0.f;
			m_fire->m_delay = m_fireDelay[m_nowWeapon];
		}
	}
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
	if (m_isBoostCool == false && KEYDOWN('R') &&
		(KEYPRESS(VK_UP) || KEYPRESS(VK_DOWN) || KEYPRESS(VK_LEFT) || KEYPRESS(VK_RIGHT))
		) {
		CAMERA->SetShake(0.15, 20, 10);
		char str[256];
		sprintf(str, "Dash%dSND", rand () % 2);
		SOUND->Copy(str);
		m_isBoost = m_isBoostCool = true;
		m_boostCool->m_start = 0.f;
		m_boostCool->m_delay = 3.f;

		m_moveSpd = m_originSpd * 6.5;
	}

	if (KEYPRESS(VK_LSHIFT)) m_moveSpd = m_originSpd * 0.5;
	else if(m_isBoost == false) m_moveSpd = m_originSpd;

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
			if (m_pos.x < GX(0))
				m_pos.x = GX(0);
		}
		else {
			if (m_status != P_RIGHT) {
				m_status = P_RIGHT;
				m_ani->m_nowFrame = 0;
			}
			m_pos.x += m_moveSpd * D_TIME;
			if (m_pos.x > GX(GAMESIZEX))
				m_pos.x = GX(GAMESIZEX);
		}
	}
	else {
		if (m_status != P_IDLE) {
			m_status = P_IDLE;
			m_ani->m_nowFrame = 0;
		}
	}

	if (KEYPRESS(VK_UP)) {
		m_pos.y -= m_moveSpd * D_TIME;
		if (m_pos.y < GY(0))
			m_pos.y = GY(0);
	}
	if (KEYPRESS(VK_DOWN)) {
		m_pos.y += m_moveSpd * D_TIME;
		if (m_pos.y > GY(GAMESIZEY))
			m_pos.y = GY(GAMESIZEY);
	}
}

void cPlayer::Fire()
{
	if (KEYPRESS(VK_SPACE)) {
		char str[256];

		if (m_nowWeapon == 0) sprintf(str, "Weapon0_%dSND", rand() % 9);
		else sprintf(str, "Weapon1_%dSND", rand() % 4);

		SOUND->Copy(str);
		switch (m_nowWeapon) {
		case 0:
			switch (GAME->m_level) {
			case 1:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 3, 10, m_pos, VEC2(0, -1), VEC2(2,2), 150.f, false, false, false, true);
				break;
			case 2:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 3, 10, m_pos, VEC2(0, -1), VEC2(2,2), 150.f, false, false, false, true);
				break;
			case 3:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 5, 10, m_pos, VEC2(0, -1), VEC2(2,2), 200.f, false, false, false, true);
				break;
			case 4:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 5, 10, m_pos, VEC2(0, -1), VEC2(2,2), 200.f, false, false, false, true);
				break;
			case 5:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 8, 10, m_pos, VEC2(0, -1), VEC2(2,2), 250.f, false, false, false, true);
				break;
			}
			break;
		case 1:
			switch (GAME->m_level) {
			case 1:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 1, 10, m_pos, VEC2(0, -1), VEC2(2, 2), 500.f, true);
				break;
			case 2:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 3, 10, m_pos, VEC2(0, -1), VEC2(2, 2), 500.f, true);
				break;
			case 3:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 3, 20, m_pos, VEC2(0, -1), VEC2(2, 2), 800.f, true);
				break;
			case 4:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 5, 20, m_pos, VEC2(0, -1), VEC2(2, 2), 800.f, true);
				break;
			case 5:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 8, 20, m_pos, VEC2(0, -1), VEC2(2, 2), 1000.f, true);
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
