#include "DXUT.h"
#include "cIngameUI.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	Init();
	m_fire = new cTimer(m_fireDelay[m_nowWeapon]);
	m_boostCool = new cTimer(0.3);
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
	SAFE_DELETE(m_fire);
	SAFE_DELETE(m_boostCool);
	SAFE_DELETE(m_motion);
	SAFE_DELETE(m_img);
	SAFE_DELETE(m_boostBar);
	SAFE_DELETE(m_ani);
}

void cPlayer::Update()
{
	if (m_isLive == false) {
		Dead();
		return;
	}

	if (!m_isActive || !m_isLive) return;

	m_ani->Update();

	Move();
	ChangeWeapon();

	if (m_isDamaged) {
		m_damageTime += D_TIME;
		if (m_damageTime > 2.f) {
			m_alpha = 255.f;

			m_damageTime = 0.f;
			m_isDamaged = false;
		}
	}

	if (m_isBoostCool) {
		if (m_boostCool->Update())
			m_isBoostCool = false;
	}

	MotionBlur();
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

	for(auto iter : ((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor())
		OnCollision(iter);
	for (auto iter : ((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy())
		OnCollision(iter);
	for (auto iter : ((cBulletManager*)OBJFIND(BULLET))->GetEnemyBullets())
		OnCollision(iter);
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
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true, D3DCOLOR_ARGB((int)m_alpha, 255, 255, 255));
}

void cPlayer::OnCollision(cObject* other)
{
	if (m_isDamaged) return;

	if (AABB(GetCustomCollider(5), other->GetObjCollider())) {
		CAMERA->SetShake(0.1, 10, 3);

		if (other->GetName() == "Meteor") {
			other->SetLive(false);

			if (m_isBoost) return;
			m_hp -= ((cEnemy*)other)->m_atk;
			if (m_hp < 0) m_hp = 0;
		}

		else if (other->GetName() == "Razer") {
			((cEnemy*)other)->m_hp -= 10;
			if (((cEnemy*)other)->m_hp <= 0) other->SetLive(false);

			char str[256];
			sprintf(str, "Explosion%dIMG", 1 + rand() % 7);
			auto img = IMAGE->FindMultiTexture(str);
			EFFECT->AddEffect(new cEffect(
				str, img->GetImgSize(), 0.03,
				VEC2(GetPos().x + rand() % 30 - rand() % 30, GetPos().y + rand() % 30 - rand() % 30),
				VEC2(0, 0), VEC2(0, 0), VEC2(1.5, 1.5)
			));

			sprintf(str, "EnemyHit%dSND", rand() % 4);
			SOUND->Copy(str);

			if (m_isBoost) return;
			m_hp -= ((cEnemy*)other)->m_atk;
			if (m_hp < 0) m_hp = 0;
		}

		else if (other->GetName() == "Straight") {
			((cEnemy*)other)->m_hp -= 5;
			if (((cEnemy*)other)->m_hp <= 0) other->SetLive(false);

			char str[256];
			sprintf(str, "Explosion%dIMG", 1 + rand() % 7);
			auto img = IMAGE->FindMultiTexture(str);
			EFFECT->AddEffect(new cEffect(
				str, img->GetImgSize(), 0.03,
				VEC2(GetPos().x + rand() % 30 - rand() % 30, GetPos().y + rand() % 30 - rand() % 30),
				VEC2(0, 0), VEC2(0, 0), VEC2(1.5, 1.5)
			));

			sprintf(str, "EnemyHit%dSND", rand() % 4);
			SOUND->Copy(str);

			if (m_isBoost) return;
			m_hp -= ((cEnemy*)other)->m_atk;
			if (m_hp < 0) m_hp = 0;
		}

		else if (other->GetName() == "EnemyRazer") {
			if (m_isBoost) return;
			m_hp -= ((cBullet*)other)->m_atk;
			if (m_hp < 0) m_hp = 0;
		}

		else if (other->GetName() == "EnemyStraight") {
			if (m_isBoost) return;
			m_hp -= ((cBullet*)other)->m_atk;
			if (m_hp < 0) m_hp = 0;
		}


		if (m_isBoost) return;
		SOUND->Copy("PlayerHitSND");

		auto ingameUI = ((cIngameUI*)UI->FindUI("IngameSceneUI"));
		ingameUI->m_damaged->m_a = 255.f;
		ingameUI->m_damaged->SetNowRGB();

		ingameUI->m_targetPos = VEC2(688, 595);
		Lerp(ingameUI->m_targetPos, VEC2(688, 399), (m_hpMax - m_hp) / (double)m_hpMax);

		m_isDamaged = true;
		m_damageTime = 0.f;
		m_alpha = 128.f;
	}

	if (m_isLive && m_hp == 0) {
		m_isLive = false;
		GAME->TIME_SCALE = 0.3;
		SOUND->Stop("StageBGM");
	}
}


void cPlayer::Init()
{
	GAME->m_level = 1;

	m_alpha = 255.f;

	m_originSpd = m_moveSpd = 500.f;
	m_boostTime = 0.f;

	m_isBoostCool = false;
	m_canFire = false;

	m_damageTime = 0.f;

	m_pos = GXY(GAMESIZEX / 2, GAMESIZEY - 80);
	m_size = VEC2(0.8, 0.8);

	m_nowWeapon = 0;

	//초기 무기 딜레이
	m_fireDelay[0] = 1;
	m_fireDelay[1] = 0.5;
	if(m_fire) m_fire->m_delay = m_fireDelay[m_nowWeapon];

	//초기 무기 공격력
	m_atk[0] = 5;
	m_atk[1] = 3;

	m_status = P_IDLE;
	m_isQ = false;
	m_isW = false;
	m_isBoost = false;
	m_isDamaged = false;
	m_isLive = true;

	m_hp = 20;
	m_hpMax = 20;

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
	static int cnt = 11;
	if (cnt < 111) {
		if (cnt % 10 == 0) {
			//여기가 문제인듯
			CAMERA->SetShake(0.1, 5, 5);
			SOUND->Copy("PlayerHitSND");
			char str[256];
			sprintf(str, "Explosion%dIMG", 8 + rand() % 3);
			auto text = IMAGE->FindMultiTexture(str);
			EFFECT->AddEffect(new cEffect(str, text->GetImgSize(), 0.1,
				VEC2(m_pos.x + rand() % 50 - rand() % 50, m_pos.y + rand() % 50 - rand() % 50),
				VEC2(0, 0)
			));
		}
		cnt++;
		return;
	}
	if (!SCENE->m_isSceneChange) {
		cnt = 11;
		GAME->TIME_SCALE = 1.f;
		Release();
	}
	SCENE->ChangeScene("GameOverScene", "Fade", 2.f);
}

void cPlayer::ChangeWeapon()
{
	auto ingameUI = ((cIngameUI*)UI->FindUI("IngameSceneUI"));

	for (int i = '1'; i < '1' + ingameUI->m_weapon.size(); ++i) {
		if (KEYDOWN(i)) {
			m_nowWeapon = i - '1';
			m_fire->m_start = 0.f;
			m_fire->m_delay = m_fireDelay[m_nowWeapon];
		}
	}
}

void cPlayer::Boost()
{
	m_boostTime += D_TIME;
	if (m_boostTime < 0.5)
		Lerp(m_moveSpd, m_originSpd, 0.3);
	else {
		m_moveSpd = m_originSpd;
		m_boostTime = 0.f;
		m_isBoost = false;
	}
}

void cPlayer::Move()
{
	if (m_isDamaged == false && m_isBoostCool == false && KEYDOWN('R') &&
		(KEYPRESS(VK_UP) || KEYPRESS(VK_DOWN) || KEYPRESS(VK_LEFT) || KEYPRESS(VK_RIGHT))
		) {
		CAMERA->SetShake(0.15, 20, 10);
		char str[256];
		sprintf(str, "Dash%dSND", rand() % 2);
		SOUND->Copy(str);
		m_isBoost = m_isBoostCool = true;
		m_boostCool->m_start = 0.f;

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
		char str[256] = "";

		if (m_nowWeapon == 0) sprintf(str, "Weapon0_%dSND", rand() % 9);
		else if(m_nowWeapon == 1) sprintf(str, "Weapon1_%dSND", rand() % 4);

		SOUND->Copy(str);
		switch (m_nowWeapon) {
		case 0:
			switch (GAME->m_level) {
			case 1:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 3, 10, m_pos, VEC2(0, -1), VEC2(2,2), 150.f, 0, false, false, false, true);
				break;
			case 2:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 3, 10, m_pos, VEC2(0, -1), VEC2(2,2), 150.f, 0, false, false, false, true);
				break;
			case 3:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 5, 10, m_pos, VEC2(0, -1), VEC2(2,2), 200.f, 0, false, false, false, true);
				break;
			case 4:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 5, 10, m_pos, VEC2(0, -1), VEC2(2,2), 200.f, 0, false, false, false, true);
				break;
			case 5:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 8, 10, m_pos, VEC2(0, -1), VEC2(2,2), 250.f, 0, false, false, false, true);
				break;
			}
			break;
		case 1:
			switch (GAME->m_level) {
			case 1:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 1, 10, m_pos, VEC2(0, -1), VEC2(2, 2), 500.f, 0, true);
				break;
			case 2:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 3, 10, m_pos, VEC2(0, -1), VEC2(2, 2), 500.f, 0, true);
				break;
			case 3:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 3, 20, m_pos, VEC2(0, -1), VEC2(2, 2), 800.f, 0, true);
				break;
			case 4:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 5, 20, m_pos, VEC2(0, -1), VEC2(2, 2), 800.f, 0, true);
				break;
			case 5:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 8, 20, m_pos, VEC2(0, -1), VEC2(2, 2), 1000.f, 0, true);
				break;
			}
			break;
		}
		m_canFire = false;
	}
}

void cPlayer::MotionBlur()
{
	if (m_motionInfo.size() == 0) return;
	for (int i = 0; i < m_motionInfo.size() - 1; ++i)
		m_motionInfo[i]->m_motionPos = m_motionInfo[i + 1]->m_motionPos;
	m_motionInfo[m_motionInfo.size() - 1]->m_motionPos = m_pos;
}
