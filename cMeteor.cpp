#include "DXUT.h"
#include "cMeteor.h"

cMeteor::cMeteor(string name, VEC2 pos, VEC2 size, float rot, float downSpd)
{
	m_img = new cImage;
	m_img->m_text = IMAGE->FindTexture(name);

	m_pos = pos;
	m_size = size;
	m_rot = rot;

	m_downSpd = downSpd;

	m_hp = 20;
	m_atk = 5;

	m_objName = "Meteor";
}

cMeteor::~cMeteor()
{
	SAFE_DELETE(m_img);
}

void cMeteor::Update()
{
	m_pos.y += m_downSpd * D_TIME;
	OutMapChk(200);

	auto eBullet = ((cBulletManager*)OBJFIND(BULLET))->GetPlayerBullets();
	for (auto iter : eBullet)
		if(iter->GetLive() == true)
			OnCollision((cObject*)iter);
	OnCollision(OBJFIND(PLAYER));

	if(m_isLive == false && !OutMapChk(200)) Dead();
}

void cMeteor::Render()
{
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true);
}

void cMeteor::Dead()
{
	CAMERA->SetShake(0.05, 5, 5);

	char str[256];
	sprintf(str, "RockHit%dSND", rand() % 4);
	SOUND->Copy(str);

	sprintf(str, "Explosion%dIMG", 8 + rand() % 3);
	auto img = IMAGE->FindMultiTexture(str);
	EFFECT->AddEffect(new cEffect(
		str, img->GetImgSize(), 0.01,
		VEC2(GetPos().x +  rand() % 30 - rand() % 30, GetPos().y + rand() % 30 - rand() % 30),
		VEC2(0, 0)
	));
}

void cMeteor::OnCollision(cObject* other)
{
	if (AABB(GetObjCollider(), other->GetObjCollider())) {
		if (other->GetName() == "PlayerBullet") {
			auto player = ((cPlayer*)OBJFIND(PLAYER));
			m_hp -= player->m_atk[player->m_nowWeapon];
		}
	}

	if (m_hp <= 0) m_isLive = false;
}
