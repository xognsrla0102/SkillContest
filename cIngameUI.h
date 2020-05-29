#pragma once
#include "cUI.h"

class cImage;
class cIngameUI : public cUI
{
private:
	cImage* m_bg;
	cImage* m_nowWeapon;
	cImage* m_gameName;
public:
	cIngameUI();
	virtual ~cIngameUI();
	
	virtual void Init() override;
	virtual void Render() override;
	virtual void Release() override;
};

