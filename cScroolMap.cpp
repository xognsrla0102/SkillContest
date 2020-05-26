#include "DXUT.h"
#include "cScroolMap.h"

cScroolMap::cScroolMap(cTexture* text)
{
	m_img1 = new cImage;
	m_img2 = new cImage;

	m_img1->m_img = m_img2->m_img = text;
	Init();
}

cScroolMap::~cScroolMap()
{
	SAFE_DELETE(m_img1);
	SAFE_DELETE(m_img2);
}

void cScroolMap::Init()
{
	pos1 = VEC2(0, -(FLOAT)m_img2->m_img->m_info.Height);
	pos2 = VEC2(0, 0);

	p_downSpd = 800;
}

void cScroolMap::Update()
{
	if (pos2.y > (FLOAT)m_img2->m_img->m_info.Height) {
		pos1 = VEC2(0, -(FLOAT)m_img2->m_img->m_info.Height);
		pos2 = VEC2(0, 0);
	}
	pos1.y += m_downSpd * D_TIME;
	pos2.y += m_downSpd * D_TIME;

	if (KEYDOWN(VK_UP)) GAME->TIME_SCALE+=0.1;
	else if(KEYDOWN(VK_DOWN)) GAME->TIME_SCALE-=0.1;
}

void cScroolMap::Render()
{
	IMAGE->Render(m_img1->m_img, pos1);
	IMAGE->Render(m_img2->m_img, pos2);
}

void cScroolMap::Release()
{
}
