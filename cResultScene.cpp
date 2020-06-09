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
	m_initial = "";
	m_isEnterInitial = false;
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

		if (m_isEnterInitial) {
			if (m_initial.size() && KEYDOWN(VK_BACK))
				m_initial.pop_back();
			for(int i = 'A'; i != 'Z'; ++i)
				if (m_initial.size() < 3 && KEYDOWN(i))
					m_initial += i;

			if (SCENE->m_isSceneChange == false && m_initial.size() == 3 && KEYDOWN(VK_RETURN)) {
				GAME->m_scoreList[3]->m_initial = this->m_initial;
				GAME->m_scoreList[3]->m_score = GAME->m_score;
				GAME->SortScore();
				SCENE->ChangeScene("RankScene", "Fade", 2.f);
			}
		}
		else {
			if (SCENE->m_isSceneChange == false && KEYDOWN(VK_RETURN)) {
				if (GAME->m_nowStage == 1) {
					GAME->m_nowStage++;
					SCENE->ChangeScene("StageOneScene", "Plane", 3000.f);
				}
				else {
					m_isEnterInitial = true;
				}
			}
		}
	}

}

void cResultScene::Render()
{
	IMAGE->Render(m_bg->m_text, VEC2(0, 0));
	IMAGE->DrawFont("당신의 점수 : ", VEC2(250, 300), D3DCOLOR_XRGB(255, 255, 255), 40);
	DRAW_NUM(m_scorePrint, VEC2(500, 300), 40);

	if ((int)m_nowYourScore + 2 > GAME->m_score)
		IMAGE->DrawFont("엔터를 입력하여 진행하세요.", VEC2(250, 150), D3DCOLOR_XRGB(255, 255, 0), 60);

	if (m_isEnterInitial) {
		IMAGE->DrawFont("이니셜 : ", VEC2(250, 400), D3DCOLOR_XRGB(255, 255, 255), 60);
		IMAGE->DrawFont(m_initial, VEC2(500, 400), D3DCOLOR_XRGB(255, 255, 0), 60);
	}
}

void cResultScene::Release()
{
	SOUND->Stop("ResultBGM");
}

