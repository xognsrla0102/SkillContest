#pragma once
#include "cUI.h"

class cImage;
class cButton;
class cTitleUI : public cUI
{
private:
	cImage* m_titleName;
	VEC2 m_namePos;
	vector<cButton*> m_buttons;
	int m_nowButton = 0;
public:
	cTitleUI();
	virtual ~cTitleUI();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

