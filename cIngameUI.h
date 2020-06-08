#pragma once
#include "cUI.h"

class cImage;
class cIngameUI : public cUI
{
private:
	cImage* m_bg;
	cImage* m_nowWeapon;
	cImage* m_gameName;
	cImage* m_level;
	cImage* m_expBar;
	cImage* m_backWhite;
	cImage* m_player;
	cImage* m_pCore;
	cImage* m_noQ;
	cImage* m_noW;
	cImage* m_qCool;
	cImage* m_wCool;
	cImage* m_bossHP;
public:
	cAnimation* m_shadowAni;
	vector<cImage*> m_weapon;
	VEC2 m_targetPos;

	cImage* m_hp;
	cImage* m_damaged;
	cImage* m_planet;
public:
	cIngameUI();
	virtual ~cIngameUI();
	
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

