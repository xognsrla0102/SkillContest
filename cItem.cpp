#include "DXUT.h"
#include "cPlayer.h"
#include "cIngameUI.h"
#include "cItem.h"

cItem::cItem(string key, VEC2 pos, VEC2 endPos)
{
	m_key = key;
	m_img = new cImage;
	m_img->m_text = IMAGE->FindTexture(key);
	m_pos = pos;
	m_endPos = endPos;
}

cItem::~cItem()
{
	SAFE_DELETE(m_img);
}

void cItem::Update()
{
	cPlayer* player = ((cPlayer*)OBJFIND(PLAYER));

	if (m_isEndPos == FALSE) {
		if (DistPoint(m_pos, m_endPos) < 5.f) m_isEndPos = TRUE;
		else Lerp(m_pos, m_endPos, 0.03);
	}
	else {
		//0.5초만에 원래 속도 도달
		if (m_accel < 1.f) m_accel += D_TIME * 2;
		else m_accel = 1.f;
		m_pos.y += 200.f * D_TIME * m_accel;
	}

}

void cItem::Render()
{
	IMAGE->Render(m_img->m_text, m_pos, VEC2(1, 1), 0.f, true);
}

void cItem::Collision()
{
	cPlayer* player = ((cPlayer*)OBJFIND(PLAYER));

	if (m_isEndPos == FALSE) return;

	VEC2 playerPos = player->GetPos();

	RECT itemRect = {
		m_pos.x - m_img->m_text->m_info.Width  / 2 * m_size.x,
		m_pos.y - m_img->m_text->m_info.Height / 2 * m_size.y,
		m_pos.x + m_img->m_text->m_info.Width  / 2 * m_size.x,
		m_pos.y + m_img->m_text->m_info.Height / 2 * m_size.y
	};

	RECT playerRect = {
		playerPos.x - player->GetImg()->m_info.Width  / 2 * player->GetSize().x,
		playerPos.y - player->GetImg()->m_info.Height / 2 * player->GetSize().y,
		playerPos.x + player->GetImg()->m_info.Width  / 2 * player->GetSize().x,
		playerPos.y + player->GetImg()->m_info.Height / 2 * player->GetSize().y
	};

	if (AABB(itemRect, playerRect)) {
		SOUND->Copy("GetItemSND");
		SOUND->Copy("GetItemSND");
		SOUND->Copy("GetItemSND");

		if (m_key == "ItemHpIMG") {
			player->m_hp += player->m_hpMax / 5.f;
			if (player->m_hp > player->m_hpMax) {
				player->m_hp = player->m_hpMax;
			}
			auto ingameUI = ((cIngameUI*)UI->FindUI("IngameSceneUI"));
			ingameUI->m_targetPos = VEC2(688, 595);
			Lerp(ingameUI->m_targetPos, VEC2(688, 399), (player->m_hpMax - player->m_hp) / (double)player->m_hpMax);
		}
		else if (m_key == "ItemLevelUpIMG") {
			if (GAME->m_level != 5) GAME->m_nowExp = GAME->m_expMax;
		}
		else if (m_key == "ItemSkillTimeIMG") {
			player->m_isQ = false;
			player->m_Qtime = 0.f;

			player->m_isW = false;
			player->m_Wtime = 0.f;
		}
		m_isLive = FALSE;
	}
}

