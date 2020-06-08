#include "DXUT.h"
#include "cEnemyManager.h"
#include "cBullet.h"

cBullet::cBullet(const string& imageName, VEC2 pos, VEC2 dir, float rot, float bulletSpd, VEC2 size, bool isHoming, bool isFaccel, bool isSaccel)
{
	m_bulletSpd = bulletSpd;

	m_img = new cImage;
	m_img->m_text = IMAGE->FindTexture(imageName);

	m_pos = pos;
	m_dir = dir;
	m_rot = rot;
	m_size = size;
	m_isHoming = isHoming;

	if (isFaccel) {
		m_isFaccel = isFaccel;
		m_bulletSpd /= 2;
		m_accel = 1.f;
	}
	else if (isSaccel) {
		m_isSaccel = isSaccel;
		m_bulletSpd *= 2;
		m_accel = 4.f;
	}
	else {
		m_accel = 1.f;
	}
}

cBullet::~cBullet()
{
	SAFE_DELETE(m_img);
}

void cBullet::Update()
{
	auto enemy = (cEnemyManager*)OBJFIND(ENEMY);
	for(auto iter : enemy->GetMeteor())
		if(iter->GetLive())
			OnCollision(iter);
	for (auto iter : enemy->GetEnemy())
		if (iter->GetLive())
			OnCollision(iter);
	if(enemy->m_boss)
		OnCollision((cObject*)enemy->m_boss);
	if(enemy->m_mBoss)
		OnCollision((cObject*)enemy->m_mBoss);

	if (m_objName == "PlayerBullet") OutMapChk(0);
	else OutMapChk(200);

	if (m_isHoming) Homing();

	if (m_isFaccel) {
		if (m_accel > 4.f) m_accel = 4.f;
		else m_accel += D_TIME * 10;
	}
	else if (m_isSaccel) {
		if (m_accel < 1.f) m_accel = 1.f;
		else m_accel -= D_TIME * 10;
	}
	m_pos += m_dir * m_bulletSpd * D_TIME * m_accel;

	if (m_isLive == false) {
		if (m_objName == "PlayerBullet") {
			if (!OutMapChk(0)) Dead();
		}
		else {
			if (!OutMapChk(200)) Dead();
		}
	}
}

void cBullet::Render()
{
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true, m_img->m_color);
}

void cBullet::OnCollision(cObject* other)
{
	if (AABB(GetObjCollider(), other->GetObjCollider())) {
		if (GetName() == "PlayerBullet") {
			string name = other->GetName();

			if (name == "Razer" || name == "Straight" || name == "Rotate" || name == "MidBoss" || name == "Boss") {
				char str[256];
				sprintf(str, "EnemyHit%dSND", rand() % 4);
				SOUND->Copy(str);
			}
			else if (name == "Meteor") {
				char str[256];
				sprintf(str, "RockHit%dSND", rand() % 4);
				SOUND->Copy(str);
			}

			if (other->GetName() == "Radial") return;

			auto player = ((cPlayer*)OBJFIND(PLAYER));
			((cEnemy*)other)->m_hp -= player->m_atk[player->m_nowWeapon];
			if (((cEnemy*)other)->m_hp <= 0) {
				other->SetLive(false);
				int getScore = 0;
				if (name == "Razer")		 getScore = 500 * GAME->m_level / 2.f;
				else if (name == "Straight") getScore = 200 * GAME->m_level / 2.f;
				else if (name == "Rotate")	 getScore = 500 * GAME->m_level / 2.f;
				else if (name == "MidBoss") {
					GAME->m_isMidBoss = false;
					((cEnemyManager*)OBJFIND(ENEMY))->Release();
					getScore = 5000 * GAME->m_level / 2.f;
				}
				else if (name == "Boss") {
					GAME->m_isBoss = false;
					((cEnemyManager*)OBJFIND(ENEMY))->Release();
					getScore = 20000 * GAME->m_level / 2.f;
				}

				if (name != "Meteor") {
					GAME->m_score += getScore;
					FONT->AddFont("+" + to_string(getScore) + "EXP", m_pos, 1.f, true);
					if (GAME->m_level == 5) getScore = 0;
					GAME->m_nowExp += getScore;
				}
			}
			m_isLive = false;
		}
	}
}

void cBullet::Dead()
{
	if (m_objName == "PlayerBullet") {
		CAMERA->SetShake(0.05, 5, 5);

		char str[256];
		sprintf(str, "RocketHit%dSND", rand() % 5);
		SOUND->Copy(str);

		sprintf(str, "Explosion%dIMG", 1 + rand() % 7);
		auto img = IMAGE->FindMultiTexture(str);
		EFFECT->AddEffect(new cEffect(
			str, img->GetImgSize(), 0.03,
			VEC2(GetPos().x + rand() % 30 - rand() % 30, GetPos().y + rand() % 30 - rand() % 30),
			VEC2(0, 0), VEC2(0, 0), VEC2(1.5, 1.5)
		));
	}
	m_isLive = false;
}

void cBullet::Homing()
{
}
