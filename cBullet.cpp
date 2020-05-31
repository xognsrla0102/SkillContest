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
	for(auto iter : ((cEnemyManager*)OBJFIND(ENEMY))->GetMeteor())
		OnCollision((cObject*)iter);

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

	if (m_isLive == false && !OutMapChk(200)) Dead();
}

void cBullet::Render()
{
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true, m_img->m_color);
}

void cBullet::OnCollision(cObject* other)
{
	if (AABB(GetObjCollider(), other->GetObjCollider())) {
		if (other->GetName() == "Meteor") {
			SOUND->Copy("HitSND");
			SOUND->Copy("HitSND");
			m_isLive = false;
		}
	}
}

void cBullet::Dead()
{
	char str[256];
	sprintf(str, "Explosion%dSND", rand() % 6);
	SOUND->Copy(str);
	SOUND->Copy(str);

	sprintf(str, "Explosion%dIMG", 8 + rand() % 3);
	auto img = IMAGE->FindMultiTexture(str);
	EFFECT->AddEffect(new cEffect(
		str, img->GetImgSize(), 0.01,
		VEC2(GetPos().x + rand() % 30 - rand() % 30, GetPos().y + rand() % 30 - rand() % 30),
		VEC2(0, 0)
	));
	m_isLive = false;
}

void cBullet::Homing()
{
}
