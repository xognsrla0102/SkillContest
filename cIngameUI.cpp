#include "DXUT.h"
#include "cPlayer.h"
#include "cImage.h"
#include "cIngameUI.h"

cIngameUI::cIngameUI()
{
	m_bg = new cImage;
	m_nowWeapon = new cImage;
	m_gameName = new cImage;
}

cIngameUI::~cIngameUI()
{
	SAFE_DELETE(m_bg);
	SAFE_DELETE(m_nowWeapon);
	SAFE_DELETE(m_gameName);
}

void cIngameUI::Init()
{
	m_bg->m_text = IMAGE->FindTexture("IngameBGUI");
	m_nowWeapon->m_text = IMAGE->FindTexture("IngameWeaponUI");
	m_gameName->m_text = IMAGE->FindTexture("IngameStarUI");
}

void cIngameUI::Render()
{
	IMAGE->Render(m_bg->m_text, VEC2(0, 0));

	int weapon = ((cPlayer*)OBJFIND(PLAYER))->m_nowWeapon;
	IMAGE->Render(m_nowWeapon->m_text, VEC2(190 + 76 * weapon, 642), VEC2(1, 1), 0.f, true);

	IMAGE->Render(m_gameName->m_text, VEC2(790, 200), VEC2(1, 1), 0.f, true);
}

void cIngameUI::Release()
{
}
