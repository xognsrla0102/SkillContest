#include "DXUT.h"
#include "cMeteor.h"

cMeteor::cMeteor(string name, VEC2 pos, VEC2 size, float rot, float downSpd)
	: cEnemy()
{
	m_img = new cImage;
	m_img->m_text = IMAGE->FindTexture(name);

	m_pos = pos;
	m_size = size;
	m_rot = rot;

	m_downSpd = downSpd;

	m_hp = 20;
	m_atk = 1;

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
	if(m_isLive == false && !OutMapChk(200))
		Dead();
}

void cMeteor::Render()
{
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true);
}

void cMeteor::Dead()
{
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

