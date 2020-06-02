#include "DXUT.h"
#include "cButton.h"

cButton::cButton(VEC2 pos, VEC2 deltaSize, VEC2 size)
{
	m_size = size;
	m_pos = pos;
	m_rot = 0;
	m_oldSize = m_size;
	m_deltaSize = deltaSize;
}

void cButton::Update()
{
	if (m_isOn == TRUE) {
		Lerp(m_a, 255.f, 0.25);
		Lerp(m_size, m_oldSize + m_deltaSize, 0.25);
	}
	else if (m_isOn == FALSE) {
		Lerp(m_a, 150.f, 0.25);
		Lerp(m_size, m_oldSize, 0.25);
	}
}

void cButton::Render()
{
	IMAGE->Render(m_text, m_pos, m_size, m_rot, true, D3DCOLOR_ARGB((int)m_a, 255, 255, 255));
}

void cButton::SetImage(string key)
{
	m_text = IMAGE->FindTexture(key);
}
