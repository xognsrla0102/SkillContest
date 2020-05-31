#include "DXUT.h"
#include "cEffect.h"

cEffect::cEffect(const string name, int imgCnt, float delay, VEC2 pos, VEC2 dir, VEC2 velSize, VEC2 size, FLOAT alphaSpeed, VEC4 argb)
{
	m_imgName = name;

	m_imgCnt = imgCnt;

	m_delay = delay;
	m_pos = pos;
	m_dir = dir;
	m_velSize = velSize;
	m_size = size;
	m_alphaSpeed = alphaSpeed;

	m_a = argb.x;
	m_r = argb.y;
	m_g = argb.z;
	m_b = argb.w;

	SetColor();

	m_ani = new cAnimation(delay, imgCnt, true);
}

cEffect::~cEffect()
{
	SAFE_DELETE(m_ani);
}

void cEffect::Update()
{
	m_ani->Update();

	m_pos += m_dir * 300.f * D_TIME;

	if (m_size.x > 0.f) m_size += m_velSize * 10 * D_TIME;
	else if (m_size.x < 0.f) m_size = VEC2(0, 0);

	m_a -= m_alphaSpeed * D_TIME;
	if (m_ani->m_nowFrame == m_imgCnt - 1) {
		m_a = 0.f;
		m_isDone = TRUE;
	}
	SetColor();
}

void cEffect::Render()
{
	cTexture* nowImg = IMAGE->FindTexture(m_imgName, m_ani->m_nowFrame);
	IMAGE->Render(nowImg, m_pos, m_size, 0.f, true, m_color);
}
