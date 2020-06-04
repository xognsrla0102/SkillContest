#include "DXUT.h"
#include "cPlayer.h"
#include "cImage.h"
#include "cIngameUI.h"

cIngameUI::cIngameUI()
{
	m_bg = new cImage;
	m_nowWeapon = new cImage;
	m_gameName = new cImage;
	m_level = new cImage;
	m_expBar = new cImage;
	m_backWhite = new cImage;
	m_player = new cImage;
	m_damaged = new cImage;
	m_pCore = new cImage;
	m_hp = new cImage;

	m_weapon.push_back(new cImage);
	m_weapon.push_back(new cImage);
}

cIngameUI::~cIngameUI()
{
	SAFE_DELETE(m_bg);
	SAFE_DELETE(m_nowWeapon);
	SAFE_DELETE(m_gameName);
	SAFE_DELETE(m_level);
	SAFE_DELETE(m_expBar);
	SAFE_DELETE(m_backWhite);
	SAFE_DELETE(m_player);
	SAFE_DELETE(m_damaged);
	SAFE_DELETE(m_pCore);
	SAFE_DELETE(m_hp);

	for (auto iter : m_weapon)
		SAFE_DELETE(iter);
	m_weapon.clear();
}

void cIngameUI::Init()
{
	m_bg->m_text = IMAGE->FindTexture("IngameBGUI");
	m_nowWeapon->m_text = IMAGE->FindTexture("IngameWeaponUI");
	m_gameName->m_text = IMAGE->FindTexture("IngameStarUI");
	m_level->m_text = IMAGE->FindTexture("IngameLevelUI");
	m_expBar->m_text = IMAGE->FindTexture("IngameExpUI");
	m_backWhite->m_text = IMAGE->FindTexture("IngameBackWhiteUI");
	m_pCore->m_text = IMAGE->FindTexture("PlayerCore");
	m_hp->m_text = IMAGE->FindTexture("IngameHpUI");
	m_hp->m_pos = m_targetPos = VEC2(688, 595);

	for (int i = 0; i < 2; ++i) {
		char str[256];
		sprintf(str, "PlayerBullet%dIMG", i);
		m_weapon[i]->m_text = IMAGE->FindTexture(str);
	}
	m_weapon[0]->m_pos = VEC2(190, 660);
	m_weapon[1]->m_pos = VEC2(190 + 75, 640);

	m_pPos = VEC2(710, 420);
	m_pShakeTime = 0.f;

	m_damaged->m_text = IMAGE->FindTexture("IngameDamagedUI");
	m_damaged->m_a = 0.f;
	m_damaged->SetNowRGB();
}

void cIngameUI::Update()
{
	if ((int)m_damaged->m_a != 0) {
		Lerp(m_damaged->m_a, 0.f, 0.05);
		m_damaged->SetNowRGB();
		
		m_pShakeTime += D_TIME;

		if (m_pShakeTime < 0.2f) {
			m_pPos.x += rand() % 30 - rand() % 30;
			m_pPos.y += rand() % 30 - rand() % 30;
		}
		else{
			m_pShakeTime = 0.f;
			m_pPos = VEC2(710, 420);

			m_damaged->m_a = 0.f;
			m_damaged->SetNowRGB();
		}
	}
	Lerp(m_hp->m_pos, m_targetPos, 0.10);
}

void cIngameUI::Render()
{
	IMAGE->ReBegin(false);
	IMAGE->Render(m_pCore->m_text, OBJFIND(PLAYER)->GetPos(), VEC2(1, 1), 0.f, true);
	IMAGE->ReBegin(true);

	P_STATUS status = ((cPlayer*)OBJFIND(PLAYER))->m_status;
	cAnimation* ani = OBJFIND(PLAYER)->GetAni();

	if (status == P_IDLE)
		m_player->m_text = IMAGE->FindTexture("PlayerIdle");
	else if (status == P_LEFT)
		m_player->m_text = IMAGE->FindTexture("PlayerLeft", ani->m_nowFrame);
	else if (status == P_RIGHT)
		m_player->m_text = IMAGE->FindTexture("PlayerRight", ani->m_nowFrame);

	IMAGE->Render(m_backWhite->m_text, VEC2(680, 100));
	IMAGE->Render(m_player->m_text, m_pPos, VEC2(1.8, 1.8));
	IMAGE->Render(m_damaged->m_text, VEC2(40, 40), VEC2(1, 1), 0.f, false, m_damaged->m_color);

	IMAGE->Render(m_hp->m_text, m_hp->m_pos);

	IMAGE->Render(m_bg->m_text, VEC2(0, 0));

	for (auto iter : m_weapon)
		IMAGE->Render(iter->m_text, iter->m_pos, VEC2(1.8, 1.8), 0.f, true);

	int weapon = ((cPlayer*)OBJFIND(PLAYER))->m_nowWeapon;
	IMAGE->Render(m_nowWeapon->m_text, VEC2(190 + 76 * weapon, 642), VEC2(1, 1), 0.f, true);
	IMAGE->Render(m_gameName->m_text, VEC2(785, 200), VEC2(1, 1), 0.f, true);
	for (size_t i = 0; i < GAME->m_level; ++i)
		IMAGE->Render(m_level->m_text, VEC2(710 + 40 * i, 370), VEC2(1, 1), 0.f, true);

	char str[256];
	int score = GAME->m_totalExp;
	sprintf(str, "%09d", score);
	DRAW_NUM(string(str), VEC2(830, 30), 40);

	float result = GAME->m_nowExp / (float)GAME->m_expMax;
	RECT rt = {
		0, 0,
		m_expBar->m_text->m_info.Width * result,
		m_expBar->m_text->m_info.Height
	};
	IMAGE->CropRender(m_expBar->m_text, VEC2(685, 606), VEC2(1, 1), rt, false);

	result *= 100;
	if (GAME->m_level == 5) result = 0;
	DRAW_FLOAT_SIZE(to_string(result), VEC2(690, 630), 5, 16, 15, VEC2(0.3, 0.3));
}

void cIngameUI::Release()
{
}
