#include "DXUT.h"
#include "cTimer.h"
#include "cFontManager.h"


//폰트 부분 -------------------------------------------------
cFontInfo::cFontInfo(string text, VEC2 pos, INT printTime, BOOL isScoreText, D3DCOLOR color)
	: m_text(text), m_pos(pos), m_isScoreText(isScoreText), m_color(color)
{
	m_timer = new cTimer(printTime);
}

cFontInfo::~cFontInfo()
{
	SAFE_DELETE(m_timer);
}

void cFontInfo::Update()
{
	if (m_timer->Update()) m_isDone = TRUE;
	else if (m_isScoreText == TRUE) m_pos.y -= 50.f * D_TIME;
}

void cFontInfo::Render()
{
	IMAGE->DrawFont(m_text, m_pos, m_color);
}


//폰트매니저 부분 -------------------------------------------------


cFontManager::~cFontManager()
{
	Release();
}

void cFontManager::Update()
{
	size_t size = m_fonts.size();
	for (size_t i = 0; i < size; ++i) {
		m_fonts[i]->Update();
		if (m_fonts[i]->m_isDone == TRUE) {
			SAFE_DELETE(m_fonts[i]);
			m_fonts.erase(m_fonts.begin() + i);
			i--, size--;
		}
	}
}

void cFontManager::Render()
{
	for (auto iter : m_fonts)
		iter->Render();
}

void cFontManager::Release()
{
	for (auto iter : m_fonts)
		SAFE_DELETE(iter);
	m_fonts.clear();
}

void cFontManager::AddFont(string text, VEC2 pos, INT printTime, BOOL isScoreText, D3DCOLOR color)
{
	m_fonts.push_back(new cFontInfo(text, pos, printTime, isScoreText, color));
}

