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

	m_hp = 20 + GAME->m_level * GAME->m_level / 2.f;
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
}

void cMeteor::Render()
{
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true);
}

