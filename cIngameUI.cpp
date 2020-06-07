#include "DXUT.h"
#include "cPlayer.h"
#include "cImage.h"
#include "cIngameUI.h"

cIngameUI::cIngameUI()
{
	m_shadowAni = new cAnimation(0.1, 17, true);

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
	m_noQ = new cImage;
	m_noW = new cImage;
	m_qCool = new cImage;
	m_wCool = new cImage;
	m_planet = new cImage;

	m_weapon.push_back(new cImage);
	m_weapon.push_back(new cImage);
	m_weapon.push_back(new cImage);
}

cIngameUI::~cIngameUI()
{
	SAFE_DELETE(m_shadowAni);

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

	SAFE_DELETE(m_noQ);
	SAFE_DELETE(m_noW);
	SAFE_DELETE(m_qCool);
	SAFE_DELETE(m_wCool);
	SAFE_DELETE(m_planet);

	for (auto iter : m_weapon)
		SAFE_DELETE(iter);
	m_weapon.clear();
}

void cIngameUI::Init()
{
	m_shadowAni->m_nowFrame = 0;

	m_bg->m_text = IMAGE->FindTexture("IngameBGUI");
	m_nowWeapon->m_text = IMAGE->FindTexture("IngameWeaponUI");
	m_gameName->m_text = IMAGE->FindTexture("IngameStarUI");
	m_level->m_text = IMAGE->FindTexture("IngameLevelUI");
	m_expBar->m_text = IMAGE->FindTexture("IngameExpUI");
	m_backWhite->m_text = IMAGE->FindTexture("IngameBackWhiteUI");
	m_pCore->m_text = IMAGE->FindTexture("PlayerCore");
	m_hp->m_text = IMAGE->FindTexture("IngameHpUI");
	m_hp->m_pos = m_targetPos = VEC2(688, 595);

	m_noQ->m_text = IMAGE->FindTexture("IngameNoSkillUI");
	m_noW->m_text = IMAGE->FindTexture("IngameNoSkillUI");

	m_qCool->m_text = IMAGE->FindTexture("IngameSkillUI");
	m_wCool->m_text = IMAGE->FindTexture("IngameSkillUI");

	for (int i = 0; i < 2; ++i) {
		char str[256];
		sprintf(str, "PlayerBullet%dIMG", i);
		m_weapon[i]->m_text = IMAGE->FindTexture(str);
	}
	m_weapon[0]->m_pos = VEC2(265, 660);
	m_weapon[1]->m_pos = VEC2(265 + 75, 640);
	m_weapon[2]->m_pos = VEC2(265 + 150, 640);

	m_damaged->m_text = IMAGE->FindTexture("IngameDamagedUI");
	m_damaged->m_a = 0.f;
	m_damaged->SetNowRGB();
}

void cIngameUI::Update()
{
	if ((int)m_damaged->m_a != 0) {
		Lerp(m_damaged->m_a, 0.f, 0.03);
		m_damaged->SetNowRGB();
	}
	else {
		m_damaged->m_a = 0.f;
		m_damaged->SetNowRGB();
	}

	if (((cPlayer*)OBJFIND(PLAYER))->m_isW) {
		m_shadowAni->Update();
		if (m_shadowAni->m_nowFrame == m_shadowAni->m_endFrame / 2) {
			CAMERA->SetShake(0.3, 10, 10);

			char str[256];
			sprintf(str, "EnemyHit%dSND", rand() % 4);
			SOUND->Copy(str);

			for (auto iter : ((cEnemyManager*)OBJFIND(ENEMY))->GetEnemy()) {
				sprintf(str, "Explosion%dIMG", 1 + rand() % 7);
				auto img = IMAGE->FindMultiTexture(str);
				EFFECT->AddEffect(new cEffect(
					str, img->GetImgSize(), 0.03,
					VEC2(iter->GetPos().x + rand() % 30 - rand() % 30, iter->GetPos().y + rand() % 30 - rand() % 30),
					VEC2(0, 0), VEC2(0, 0), VEC2(1.5, 1.5)
				));
			}

			((cBulletManager*)OBJFIND(BULLET))->Reset();
			((cEnemyManager*)OBJFIND(ENEMY))->Release();

			GAME->m_isNotDead = false;
		}
	}

	Lerp(m_hp->m_pos, m_targetPos, 0.10);
}

void cIngameUI::Render()
{
	IMAGE->ReBegin(false);
	IMAGE->Render(m_pCore->m_text, OBJFIND(PLAYER)->GetPos(), VEC2(1, 1), 0.f, true);
	IMAGE->ReBegin(true);

	if (((cPlayer*)OBJFIND(PLAYER))->m_isW && m_shadowAni->m_nowFrame < m_shadowAni->m_endFrame - 1) {
		IMAGE->Render(m_planet->m_text, VEC2(340, 350), VEC2(0.3, 0.3), 0.f, true);
		IMAGE->Render(IMAGE->FindTexture("ShadowIMG", m_shadowAni->m_nowFrame), VEC2(340, 350), VEC2(0.3, 0.3), 0.f, true);
	}

	P_STATUS status = ((cPlayer*)OBJFIND(PLAYER))->m_status;
	cAnimation* ani = OBJFIND(PLAYER)->GetAni();

	if (status == P_IDLE)
		m_player->m_text = IMAGE->FindTexture("PlayerIdle");
	else if (status == P_LEFT)
		m_player->m_text = IMAGE->FindTexture("PlayerLeft", ani->m_nowFrame);
	else if (status == P_RIGHT)
		m_player->m_text = IMAGE->FindTexture("PlayerRight", ani->m_nowFrame);

	IMAGE->Render(m_backWhite->m_text, VEC2(680, 100));
	IMAGE->Render(m_player->m_text, VEC2(710, 420), VEC2(1.8, 1.8));
	IMAGE->Render(m_damaged->m_text, VEC2(40, 40), VEC2(1, 1), 0.f, false, m_damaged->m_color);

	IMAGE->Render(m_hp->m_text, m_hp->m_pos);

	IMAGE->Render(m_bg->m_text, VEC2(0, 0));

	for (size_t i = 0; i < m_weapon.size(); ++i) {
		if (i == 2) if (!((cPlayer*)OBJFIND(PLAYER))->m_isSteal) break;
		IMAGE->Render(m_weapon[i]->m_text, m_weapon[i]->m_pos, VEC2(1.8, 1.8), 0.f, true);
	}

	int weapon = ((cPlayer*)OBJFIND(PLAYER))->m_nowWeapon;
	IMAGE->Render(m_nowWeapon->m_text, VEC2(265 + 76 * weapon, 642), VEC2(1, 1), 0.f, true);
	IMAGE->Render(m_gameName->m_text, VEC2(785, 200), VEC2(1, 1), 0.f, true);
	for (size_t i = 0; i < GAME->m_level; ++i)
		IMAGE->Render(m_level->m_text, VEC2(710 + 40 * i, 370), VEC2(1, 1), 0.f, true);

	char str[256];
	int score = GAME->m_score;
	sprintf(str, "%09d", score);
	DRAW_NUM(string(str), VEC2(830, 30), 40);

	auto player = ((cPlayer*)OBJFIND(PLAYER));
	if (player->m_isQ || GAME->m_level < 3) IMAGE->Render(m_noQ->m_text, VEC2(923, 422));
	if (player->m_isW || GAME->m_level < 5) IMAGE->Render(m_noW->m_text, VEC2(1081, 422));

	float result;

	result = player->m_Qtime / 10.f;
	RECT rt = {
		0, 0,
		m_qCool->m_text->m_info.Width * result,
		m_qCool->m_text->m_info.Height
	};
	IMAGE->CropRender(m_qCool->m_text, VEC2(920, 540), VEC2(1, 1), rt);

	result = player->m_Wtime / 30.f;
	rt = {
		0, 0,
		(LONG)(m_wCool->m_text->m_info.Width * result),
		(LONG)m_wCool->m_text->m_info.Height
	};
	IMAGE->CropRender(m_wCool->m_text, VEC2(1076, 540), VEC2(1, 1), rt);

	result = GAME->m_nowExp / (float)GAME->m_expMax;
	rt = {
		0, 0,
		(LONG)(m_expBar->m_text->m_info.Width * result),
		(LONG)m_expBar->m_text->m_info.Height
	};
	IMAGE->CropRender(m_expBar->m_text, VEC2(685, 606), VEC2(1, 1), rt);
	//점수 백분율
	result *= 100;
	if (GAME->m_level == 5) result = 0;
	DRAW_FLOAT_SIZE(to_string(result), VEC2(690, 630), 5, 16, 15, VEC2(0.3, 0.3));

	if (GAME->m_isDebugInfo) {
		IMAGE->DrawFont("플레이어 레벨 : " + to_string(GAME->m_level), VEC2(475, 52));
		IMAGE->DrawFont("누적 경험치  : " + to_string(GAME->m_score), VEC2(420, 80));
		for (int i = 2; i <= 4; ++i) {
			IMAGE->DrawFont(to_string(i) + "레벨 필요한 경험치 : " + to_string(4000 + 1500 * (i - 2)), VEC2(370, 80 + 30 * (i - 1)));
		}
	}
}

void cIngameUI::Release()
{
}
