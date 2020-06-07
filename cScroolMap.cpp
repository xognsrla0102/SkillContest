#include "DXUT.h"
#include "cScroolMap.h"

cScroolMap::cScroolMap(cTexture* text)
{
	m_img1 = new cImage;
	m_img2 = new cImage;
	m_createGas = new cTimer(-1);

	m_img1->m_text = m_img2->m_text = text;
	Init();
}

cScroolMap::~cScroolMap()
{
	Release();

	SAFE_DELETE(m_img1);
	SAFE_DELETE(m_img2);

	SAFE_DELETE(m_createGas);
}

void cScroolMap::Init()
{
	pos1 = VEC2(0, -(FLOAT)m_img2->m_text->m_info.Height);
	pos2 = VEC2(0, 0);

	m_mapSpd = 200;
	m_gasSpd = 500;
}

void cScroolMap::Update()
{
	if (m_createGas->Update()) {
		m_createGas->m_delay = 2.f + rand() % 3;
		m_gas.push_back(new cImage);
		m_gas[m_gas.size() - 1]->m_text = IMAGE->FindTexture("CloudIMG", rand() % 4);
		int height = m_gas[m_gas.size() - 1]->m_text->m_info.Height;
		m_gas[m_gas.size() - 1]->m_pos = GXY(100 * (rand() % 3), -height);
	}

	pos1.y += m_mapSpd * D_TIME;
	pos2.y += m_mapSpd * D_TIME;

	if (pos2.y >= (FLOAT)m_img2->m_text->m_info.Height) {
		pos1 = VEC2(0, -(FLOAT)m_img2->m_text->m_info.Height);
		pos2 = VEC2(0, 0);
	}

	size_t size = m_gas.size();
	for(int i = 0; i < size; ++i){
		m_gas[i]->m_pos.y += m_gasSpd * D_TIME;
		if (m_gas[i]->m_pos.y > GY(GAMESIZEY)) {
			SAFE_DELETE(m_gas[i]);
			m_gas.erase(m_gas.begin() + i);
			--i, --size;
		}
	}
}

void cScroolMap::Render()
{
	IMAGE->Render(m_img1->m_text, pos1);
	IMAGE->Render(m_img2->m_text, pos2);

	for (auto iter : m_gas)
		IMAGE->Render(iter->m_text, iter->m_pos, VEC2(1, 1), 0.f);
}

void cScroolMap::Release()
{
	for (auto iter : m_gas)
		SAFE_DELETE(iter);
	m_gas.clear();
}
