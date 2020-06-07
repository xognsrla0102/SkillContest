#include "DXUT.h"
#include "cTitleUI.h"

cTitleUI::cTitleUI()
{
	m_titleName = new cImage;
	for (int i = 0; i < 3; ++i)
		m_buttons.push_back(
			new cButton(VEC2(1140, 300 + i * 150),
				VEC2(0.1, 0.1))
		);
}

cTitleUI::~cTitleUI()
{
	SAFE_DELETE(m_titleName);
	for (auto iter : m_buttons)
		SAFE_DELETE(iter);
	m_buttons.clear();
}

void cTitleUI::Init()
{
	m_titleName->m_text = IMAGE->FindTexture("TitleNameUI");
	m_namePos = VEC2(WINSIZEX, -200);

	m_buttons[0]->SetImage("TitleStartUI");
	m_buttons[1]->SetImage("TitleRankUI");
	m_buttons[2]->SetImage("TitleHelpUI");

	m_buttons[m_nowButton]->m_isOn = false;
	m_buttons[0]->m_isOn = true;
}

void cTitleUI::Update()
{
	Lerp(m_namePos, VEC2(WINSIZEX / 2 - 100, 200), 0.08);

	if (KEYDOWN(VK_UP)) {
		m_buttons[m_nowButton]->m_isOn = false;
		if (m_nowButton - 1 < 0) m_nowButton = m_buttons.size() - 1;
		else m_nowButton--;
		m_buttons[m_nowButton]->m_isOn = true;
	}
	else if (KEYDOWN(VK_DOWN)) {
		m_buttons[m_nowButton]->m_isOn = false;
		if (m_nowButton + 1 == m_buttons.size()) m_nowButton = 0;
		else m_nowButton++;
		m_buttons[m_nowButton]->m_isOn = true;
	}

	if (KEYDOWN(VK_RETURN)) {
		switch (m_nowButton) {
		case 0:
			GAME->m_nowStage = 1;
			SCENE->ChangeScene("StageOneScene", "Plane", 3000.f);
			break;
		case 1:
			break;
		case 2:
			break;
		}
	}

	for (auto iter : m_buttons)
		iter->Update();
}

void cTitleUI::Render()
{
	for (auto iter : m_buttons)
		iter->Render();
	IMAGE->Render(m_titleName->m_text, m_namePos, VEC2(1, 1), 0.f, true);
}

void cTitleUI::Release()
{
}
