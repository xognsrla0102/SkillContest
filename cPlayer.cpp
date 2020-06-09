#include "DXUT.h"
#include "cIngameUI.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	Init();
	m_fire = new cTimer(m_fireDelay[m_nowWeapon]);
	m_boostCool = new cTimer(2);
	m_motion = new cTimer(0.02);
	m_img = new cImage;
	m_boostBar = new cImage;

	m_boostBar->m_text = IMAGE->FindTexture("IngameSkillUI");
	m_ani = new cAnimation(0.13, 5, true);
	m_qAni = new cAnimation(0.08, 40, true);

	m_objName = "Player";
}

cPlayer::~cPlayer()
{
	SAFE_DELETE(m_fire);
	SAFE_DELETE(m_boostCool);
	SAFE_DELETE(m_motion);
	SAFE_DELETE(m_img);
	SAFE_DELETE(m_boostBar);
	SAFE_DELETE(m_ani);
	SAFE_DELETE(m_qAni);
	for (auto iter : m_motionInfo)
		SAFE_DELETE(iter);
}

void cPlayer::Update()
{
	if (m_isLive == false) {
		Dead();
		return;
	}

	if (!m_isActive || !m_isLive) return;

	if (m_isQ) {
		m_Qtime += D_TIME;
		if (m_qAni->m_nowFrame != m_qAni->m_endFrame - 1) {
			//이펙트 애니메이션이 다 진행될 때 까지 계속 skillQ 발동
			m_qAni->Update();
		}
		if (m_Qtime > 10.f) {
			//10초가 지나면 다시 q스킬 사용이 가능하도록 함.
			m_isQ = false;
			m_Qtime = 0.f;
		}
	}

	if (m_isW) {
		if (m_Wtime < 20.f) {
			m_Wtime += D_TIME;
		}
		else {
			m_isW = false;
			m_Wtime = 0.f;
		}
	}

	m_ani->Update();

	Move();
	Skill();
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

	auto enemy = (cEnemyManager*)OBJFIND(ENEMY);
	for (auto iter : enemy->GetMeteor())
		if (iter->GetLive())
			OnCollision(iter);
	for (auto iter : enemy->GetEnemy())
		if (iter->GetLive())
			OnCollision(iter);
	if (enemy->m_boss)
		OnCollision((cObject*)enemy->m_boss);
	if (enemy->m_mBoss)
		OnCollision((cObject*)enemy->m_mBoss);

	for (auto iter : ((cBulletManager*)OBJFIND(BULLET))->GetEnemyBullets())
		if (iter->GetLive())
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
	if(m_isQ) IMAGE->Render(IMAGE->FindTexture("SkillQIMG", m_qAni->m_nowFrame), m_pos, VEC2(1, 1), 0.f, true);
}

void cPlayer::OnCollision(cObject* other)
{
	if (m_isQ) {
		if (m_qAni->m_nowFrame < m_qAni->m_endFrame - 1) {
			if (AABB(GetObjCollider(), other->GetObjCollider())) {
				if (other->GetName() == "EnemyRazer" || other->GetName() == "EnemyStraight" ||
					other->GetName() == "EnemyRadial" || other->GetName() == "EnemyRotate") {
					other->SetLive(false);

					if (other->GetName() != "EnemyRazer") {
						SOUND->Copy("StealSND");
						SOUND->Copy("StealSND");
						SOUND->Copy("StealSND");
					}

					m_stealTanName = other->GetName();
					if (!m_isSteal) m_isSteal = true;
					auto ingameUI = ((cIngameUI*)UI->FindUI("IngameSceneUI"));
					if (m_stealTanName != "EnemyRotate")
						ingameUI->m_weapon[2]->m_text = IMAGE->FindTexture(m_stealTanName + "IMG");
					else
						ingameUI->m_weapon[2]->m_text = IMAGE->FindTexture("EnemyRadialIMG");

					if (m_nowWeapon == 2) {
						if (m_stealTanName == "EnemyStraight")    m_fire->m_delay = 0.15;
						else if (m_stealTanName == "EnemyRotate") m_fire->m_delay = 0.1;
						else if (m_stealTanName == "EnemyRadial") m_fire->m_delay = 0.1;
						else if (m_stealTanName == "EnemyRazer")  m_fire->m_delay = 0.3f;
						m_fire->m_start = 0.f;
					}
				}
				return;
			}
		}
	}

	if (GAME->m_isNotDead) return;
	if (m_isDamaged) return;

	if (AABB(GetCustomCollider(3), other->GetObjCollider())) {
		CAMERA->SetShake(0.1, 10, 3);
		if (other->GetName() == "Meteor") {
			other->SetLive(false);
			if (m_isBoost) return;
			m_hp -= ((cEnemy*)other)->m_atk;
		}

		else if (
			other->GetName() == "Razer" || other->GetName() == "Straight" || other->GetName() == "Rotate" ||
			other->GetName() == "MidBoss" || other->GetName() == "Boss"
			) {
			if (other->GetName() == "Razer")			((cEnemy*)other)->m_hp -= 10;
			else if(other->GetName() == "Straight")		((cEnemy*)other)->m_hp -= 5;
			else if (other->GetName() == "Rotate")		((cEnemy*)other)->m_hp -= 5;

			if (((cEnemy*)other)->m_hp <= 0) other->SetLive(false);
			char str[256];
			sprintf(str, "Explosion%dIMG", 1 + rand() % 7);
			auto img = IMAGE->FindMultiTexture(str);
			EFFECT->AddEffect(new cEffect(
				str, img->GetImgSize(), 0.03,
				VEC2(m_pos.x + rand() % 30 - rand() % 30, m_pos.y + rand() % 30 - rand() % 30),
				VEC2(0, 0), VEC2(0, 0), VEC2(1.5, 1.5)
			));

			sprintf(str, "EnemyHit%dSND", rand() % 4);
			SOUND->Copy(str);

			if (m_isBoost) return;
			m_hp -= 3;
		}

		else if (
			other->GetName() == "EnemyRazer" || other->GetName() == "EnemyStraight" ||
			other->GetName() == "EnemyRadial" || other->GetName() == "EnemyRotate") {
			if (m_isBoost) return;

			char str[256];
			sprintf(str, "Explosion%dIMG", 8 + rand() % 3);
			auto text = IMAGE->FindMultiTexture(str);
			EFFECT->AddEffect(new cEffect(str, text->GetImgSize(), 0.03,
				VEC2(m_pos.x + rand() % 50 - rand() % 50, m_pos.y + rand() % 50 - rand() % 50),
				VEC2(0, 0)
			));

			m_hp -= ((cBullet*)other)->m_atk;
			((cBulletManager*)OBJFIND(BULLET))->Reset();
		}

		if (m_isBoost) return;

		SOUND->Copy("PlayerHitSND");

		if (m_hp < 0) m_hp = 0;

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
	m_fireDelay[1] = 0.3;
	if(m_fire) m_fire->m_delay = m_fireDelay[m_nowWeapon];

	//초기 무기 공격력
	m_atk[0] = 2;
	m_atk[1] = 1;
	m_atk[2] = 3;

	m_status = P_IDLE;

	m_isBoost = false;
	m_isDamaged = false;
	m_isLive = true;

	m_isSteal = false;

	m_isQ = m_isW = false;
	m_Qtime = 0.f;
	m_Wtime = 0.f;

	m_hp = 20;
	m_hpMax = 20;

	auto ingameUI = ((cIngameUI*)UI->FindUI("IngameSceneUI"));
	ingameUI->m_targetPos = VEC2(688, 595);
	Lerp(ingameUI->m_targetPos, VEC2(688, 399), (m_hpMax - m_hp) / (double)m_hpMax);

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
			CAMERA->SetShake(0.5, 4, 1);
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
			if (i == '3') {
				if (!m_isSteal) return;
				else {
					if (m_stealTanName == "EnemyStraight") {
						m_fire->m_delay = 0.15;
					}
					else if (m_stealTanName == "EnemyRotate") {
						m_fire->m_delay = 0.1;
					}
					else if (m_stealTanName == "EnemyRadial") {
						m_fire->m_delay = 0.1;
					}
					else if (m_stealTanName == "EnemyRazer") {
						m_fire->m_delay = 0.3f;
					}
					m_nowWeapon = i - '1';
					m_fire->m_start = 0.f;
				}
			}
			else {
				m_nowWeapon = i - '1';
				m_fire->m_start = 0.f;
				m_fire->m_delay = m_fireDelay[m_nowWeapon];
			}
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
	if (m_isDamaged == false && m_isBoostCool == false && KEYDOWN('R')) {
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
	static int pBulletRot = 0;

	if (KEYPRESS(VK_SPACE)) {
		char str[256] = "";

		if (m_nowWeapon == 0) sprintf(str, "Weapon0_%dSND", rand() % 9);
		else if (m_nowWeapon == 1) sprintf(str, "Weapon1_%dSND", rand() % 4);
		else if (m_stealTanName != "EnemyRazer") {
			sprintf(str, "EnemyFireSND");
		}
		else if(m_stealTanName == "EnemyRazer") {
			sprintf(str, "RazerFireSND");
		}

		SOUND->Copy(str);
		switch (m_nowWeapon) {
		case 0:
			switch (GAME->m_level) {
			case 1:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 3, 10, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 150.f, 0, false, false, false, true);
				break;
			case 2:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 3, 10, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 150.f, 0, false, false, false, true);
				break;
			case 3:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 5, 10, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 200.f, 0, false, false, false, true);
				break;
			case 4:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 8, 10, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 200.f, 0, false, false, false, true);
				break;
			case 5:
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "PlayerBullet0IMG", 8, 10, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 250.f, 0, false, false, false, true);
				break;
			}
			break;
		case 1:
			switch (GAME->m_level) {
			case 1:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 1, 10, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 500.f, 0, true);
				break;
			case 2:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 2, 15, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 500.f, 0, true);
				break;
			case 3:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 3, 20, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 800.f, 0, true);
				break;
			case 4:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 3, 20, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 1000.f, 0, true);
				break;
			case 5:
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "PlayerBullet1IMG", 4, 20, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 1000.f, 0, true);
				break;
			}
			break;
		case 2:
			if (m_stealTanName == "EnemyStraight") {
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "EnemyStraightIMG", 2, 15, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 1000.f, 0);
				((cBulletManager*)OBJFIND(BULLET))->N_Straight_Tan("PlayerBullet", "EnemyStraightIMG", 2, 15, m_pos, VEC2(0, 1), VEC2(1.5, 1.5), 1000.f, 0);

				auto& pBullet = ((cBulletManager*)OBJFIND(BULLET))->GetPlayerBullets();
				pBullet.push_back(
					new cBullet("EnemyStraightIMG", VEC2(m_pos.x, m_pos.y - 7), VEC2(-1, 0), 0.f, 1000.f, VEC2(1.5, 1.5))
				);
				pBullet[pBullet.size() - 1]->SetName("PlayerBullet");
				pBullet.push_back(
					new cBullet("EnemyStraightIMG", VEC2(m_pos.x, m_pos.y + 7), VEC2(-1, 0), 0.f, 1000.f, VEC2(1.5, 1.5))
				);
				pBullet[pBullet.size() - 1]->SetName("PlayerBullet");
				pBullet.push_back(
					new cBullet("EnemyStraightIMG", VEC2(m_pos.x, m_pos.y - 7), VEC2(1, 0), 0.f, 1000.f, VEC2(1.5, 1.5))
				);
				pBullet[pBullet.size() - 1]->SetName("PlayerBullet");
				pBullet.push_back(
					new cBullet("EnemyStraightIMG", VEC2(m_pos.x, m_pos.y + 7), VEC2(1, 0), 0.f, 1000.f, VEC2(1.5, 1.5))
				);
				pBullet[pBullet.size() - 1]->SetName("PlayerBullet");
			}
			else if (m_stealTanName == "EnemyRadial") {
				VEC2 newDir;

				for (int i = 0; i < 4; ++i) {
					newDir.x = cos(D3DXToRadian(pBulletRot + i * 90));
					newDir.y = sin(D3DXToRadian(pBulletRot + i * 90));
					D3DXVec2Normalize(&newDir, &newDir);

					auto& pBullet = ((cBulletManager*)OBJFIND(BULLET))->GetPlayerBullets();

					pBullet.push_back(
						new cBullet("EnemyRadialIMG", m_pos, newDir, 0.f, 500.f, VEC2(1.5, 1.5))
					);
					pBullet[pBullet.size() - 1]->SetName("PlayerBullet");
				}

				pBulletRot += 10;
				if (pBulletRot > 360) pBulletRot -= 360;
			}
			else if (m_stealTanName == "EnemyRotate") {
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "EnemyRadialIMG", 2, 60, m_pos, VEC2(0, -1), VEC2(1.5, 1.5), 800.f, 0);
				((cBulletManager*)OBJFIND(BULLET))->N_Way_Tan("PlayerBullet", "EnemyRadialIMG", 2, 60, m_pos, VEC2(0, 1), VEC2(1.5, 1.5), 800.f, 0);
			}
			else if (m_stealTanName == "EnemyRazer") {
				auto& pBullet = ((cBulletManager*)OBJFIND(BULLET))->GetPlayerBullets();
				pBullet.push_back(
					new cBullet("EnemyRazerIMG", VEC2(m_pos.x, m_pos.y - 70), VEC2(0, -1), 0.f, 1000.f, VEC2(5, 10))
				);
				pBullet[pBullet.size() - 1]->SetName("PlayerBullet");
			}
			break;
		}
		m_canFire = false;
	}
}

void cPlayer::Skill()
{
	if (KEYDOWN('Q')) {
		if (m_isQ || GAME->m_level < 3) {
			FONT->AddFont("아직 사용할 수 없습니다.", GXY(GAMESIZEX / 2 - 100, 100), 2.f, false, D3DCOLOR_XRGB(255, 0, 0));
			SOUND->Copy("NoSkillSND");
		}
		else {
			m_isQ = true;
			m_qAni->m_nowFrame = 0;
		}
	}
	else if (KEYDOWN('W')) {
		if (m_isW || GAME->m_level < 5) {
			FONT->AddFont("아직 사용할 수 없습니다.", GXY(GAMESIZEX / 2 - 100, 100), 2.f, false, D3DCOLOR_XRGB(255, 0, 0));
			SOUND->Copy("NoSkillSND");
		}
		else {
			auto ingame = ((cIngameUI*)UI->FindUI("IngameSceneUI"));
			ingame->m_planet->m_text = IMAGE->FindTexture("PlanetIMG", rand() % 16);
			ingame->m_shadowAni->m_nowFrame = 0;
			GAME->m_isNotDead = true;
			m_isW = true;
		}
	}
}

void cPlayer::MotionBlur()
{
	if (m_motionInfo.size() == 0) return;
	for (int i = 0; i < m_motionInfo.size() - 1; ++i)
		m_motionInfo[i]->m_motionPos = m_motionInfo[i + 1]->m_motionPos;
	m_motionInfo[m_motionInfo.size() - 1]->m_motionPos = m_pos;
}
