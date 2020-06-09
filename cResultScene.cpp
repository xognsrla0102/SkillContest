#include "DXUT.h"
#include "cResultScene.h"

cResultScene::cResultScene()
{
	m_bg = new cImage;
	m_bg->m_text = IMAGE->FindTexture("ResultBG");
}

cResultScene::~cResultScene()
{
	SAFE_DELETE(m_bg);
}

void cResultScene::Init()
{
	m_nowYourScore = 0.f;
	SOUND->Play("ResultBGM", true);
	CAMERA->m_pos = VEC2(WINSIZEX / 2, WINSIZEY / 2);

	GAME->m_score += (int)(((cPlayer*)OBJFIND(PLAYER))->m_hp / (float)(((cPlayer*)OBJFIND(PLAYER))->m_hpMax) * 100000);
}

void cResultScene::Update()
{
	char str[256];
	Lerp(m_nowYourScore, (float)GAME->m_score, 0.02);
	sprintf(str, "%09d", (int)m_nowYourScore);
	m_scorePrint = str;

	if ((int)m_nowYourScore + 2 > GAME->m_score) {
		if(m_nowYourScore != GAME->m_score)
			m_nowYourScore = GAME->m_score;
		if (SCENE->m_isSceneChange == false && KEYDOWN(VK_RETURN)) {
			if (GAME->m_nowStage == 1) {
				GAME->m_nowStage++;
				SCENE->ChangeScene("StageOneScene", "Plane", 3000.f);
			}
			else {
				GAME->m_nowStage = 0;
				SCENE->ChangeScene("TitleScene", "Fade", 2.f);
			}
		}
	}
}

void cResultScene::Render()
{
	IMAGE->Render(m_bg->m_text, VEC2(0, 0));
	IMAGE->DrawFont("당신의 점수 : ", VEC2(250, 300), D3DCOLOR_XRGB(255, 255, 255), 40);
	DRAW_NUM(m_scorePrint, VEC2(500, 300), 40);
}

void cResultScene::Release()
{
	SOUND->Stop("ResultBGM");
}

