#include "DXUT.h"
#include "cLoadScene.h"
#include "cMainProc.h"

cMainProc::cMainProc()
{
	srand(time(NULL));
	
	SCENE->AddScene("LoadScene", new cLoadScene);
	SCENE->ChangeScene("LoadScene", "None", 0.f);
}

cMainProc::~cMainProc()
{
	INPUT->ReleaseInst();
	UI->ReleaseInst();
	SCENE->ReleaseInst();
	GAME->ReleaseInst();
	EFFECT->ReleaseInst();
	OBJECT->ReleaseInst();
	FONT->ReleaseInst();
	SOUND->ReleaseInst();
	IMAGE->ReleaseInst();
	CAMERA->ReleaseInst();
}

void cMainProc::Update()
{
	INPUT->Update();
	SCENE->Update();
	UI->Update();
	
	if (GAME->m_isPause) return;
	CAMERA->Update();
	
	if (KEYDOWN(VK_F4)) {
		SCENE->m_white->m_a = 0.f;
		SCENE->m_white->SetNowRGB();
		GAME->m_nowStage = 0;
		SCENE->m_plane->m_pos = VEC2(WINSIZEX + SCENE->m_plane->m_text->m_info.Width, -300);
		SCENE->ChangeScene("TitleScene", "None", 0.f);
	}
	else if (KEYDOWN(VK_F5)) {
		SCENE->m_white->m_a = 0.f;
		SCENE->m_white->SetNowRGB();
		GAME->m_nowStage = 1;
		SCENE->m_plane->m_pos = VEC2(WINSIZEX + SCENE->m_plane->m_text->m_info.Width, -300);
		SCENE->ChangeScene("StageOneScene", "None", 0.f);
	}
	else if (KEYDOWN(VK_F6)) {
		SCENE->m_white->m_a = 0.f;
		SCENE->m_white->SetNowRGB();
		GAME->m_nowStage = 2;
		SCENE->m_plane->m_pos = VEC2(WINSIZEX + SCENE->m_plane->m_text->m_info.Width, -300);
		SCENE->ChangeScene("StageOneScene", "None", 0.f);
	}
	
	if (SCENE->GetNowSceneKey() == "StageOneScene" || SCENE->GetNowSceneKey() == "StageTwoScene") {
	OBJECT->Update();
	EFFECT->Update();
	FONT->Update();
	}
}

void cMainProc::Render()
{
	CAMERA->SetTransform();
	
	IMAGE->Begin(false);
	
	SCENE->Render();
	EFFECT->Render();
	OBJECT->Render();
	FONT->Render();
	
	IMAGE->ReBegin(true);
	UI->Render();
	IMAGE->End();
}

void cMainProc::ResetDevice()
{
	CAMERA->ResetCamera();
	IMAGE->ResetDevice();
}

void cMainProc::LostDevice()
{
	IMAGE->LostDevice();
}
