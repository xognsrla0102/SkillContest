#include "DXUT.h"
#include "cPlayer.h"

cPlayer::cPlayer()
{
	m_img = new cImage;
	m_img->m_text = IMAGE->FindTexture("PlayerIMG");
	Init();
}

cPlayer::~cPlayer()
{
	SAFE_DELETE(m_img);
}

void cPlayer::Update()
{
	if (m_isActive) {
		Move();
	}
}

void cPlayer::Render()
{
	if(m_isActive)
		IMAGE->Render(m_img->m_text, m_pos, m_size, m_rot, true, m_img->m_color);
}


void cPlayer::Init()
{
	m_originSpd = m_moveSpd = 500.f;
	m_pos = VEC2(WINSIZEX / 2, WINSIZEY - 100);
	m_size = VEC2(0.5, 0.5);
}

void cPlayer::Release()
{
}

void cPlayer::Move()
{
	if (KEYPRESS(VK_LSHIFT)) m_moveSpd = m_originSpd * 0.5;
	else m_moveSpd = m_originSpd;

	if (KEYPRESS(VK_UP)) {
		m_pos.y -= m_moveSpd * D_TIME;
	}
	if (KEYPRESS(VK_DOWN)) {
		m_pos.y += m_moveSpd * D_TIME;
	}
	if (KEYPRESS(VK_LEFT)) {
		m_pos.x -= m_moveSpd * D_TIME;
	}
	if (KEYPRESS(VK_RIGHT)) {
		m_pos.x += m_moveSpd * D_TIME;
	}
}
