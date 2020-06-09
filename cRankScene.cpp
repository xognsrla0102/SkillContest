#include "DXUT.h"
#include "cRankScene.h"

cRankScene::cRankScene()
{
	m_bg = new cImage;
	m_bg->m_text = IMAGE->FindTexture("RankBG");
}

cRankScene::~cRankScene()
{
	SAFE_DELETE(m_bg);
}

void cRankScene::Init()
{
	SOUND->Play("RankBGM", true);
}

void cRankScene::Update()
{
	if (KEYDOWN(VK_RETURN))
		SCENE->ChangeScene("TitleScene", "Fade", 2.f);
}

void cRankScene::Render()
{
	IMAGE->Render(m_bg->m_text, VEC2(0, 0));

	for (size_t i = 0; i < 3; ++i) {
		IMAGE->DrawFont(GAME->m_scoreList[i]->m_initial, VEC2(650, 200 + i * 150), D3DCOLOR_XRGB(255, 255, 0), 60);
		DRAW_NUM(to_string(GAME->m_scoreList[i]->m_score), VEC2(900, 200 + i * 150), 40);
	}
}

void cRankScene::Release()
{
	SOUND->Stop("RankBGM");
}
