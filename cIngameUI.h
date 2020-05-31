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
	cImage* m_damaged;
public:
	cIngameUI();
	virtual ~cIngameUI();
	
	virtual void Init() override;
	virtual void Render() override;
	virtual void Release() override;
};

