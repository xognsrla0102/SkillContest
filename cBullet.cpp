#include "DXUT.h"
#include "cBullet.h"

cBullet::cBullet(const string& imageName, VEC2 pos, VEC2 dir, float rot, float bulletSpd, VEC2 size, bool isHoming, bool isAccel)
{
	m_bulletSpd = bulletSpd;
	m_isAccel = isAccel;

	m_img = new cImage;
	m_img->m_text = IMAGE->FindTexture(imageName);

	m_pos = pos;
	m_dir = dir;
	m_rot = rot;
	m_size = size;
	m_isHoming = isHoming;
}

cBullet::~cBullet()
{
	SAFE_DELETE(m_img);
}

void cBullet::Update()
{
	if (m_isHoming) Homing();

	if (m_isAccel) {
		if (m_accel > 4.f) m_accel = 4.f;
		else m_accel += D_TIME;
	}
	m_pos += m_dir * m_bulletSpd * D_TIME * m_accel;
}

void cBullet::Render()
{
	IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true, m_img->m_color);
}

void cBullet::Straight()
{
}

void cBullet::Homing()
{
}
