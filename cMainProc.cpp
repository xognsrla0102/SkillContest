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
	GAME->ReleaseInst();
	UI->ReleaseInst();
	SCENE->ReleaseInst();
	OBJECT->ReleaseInst();
	FONT->ReleaseInst();
	CAMERA->ReleaseInst();
	EFFECT->ReleaseInst();
	SOUND->ReleaseInst();
	IMAGE->ReleaseInst();
}

void cMainProc::Update()
{
	INPUT->Update();
	CAMERA->Update();
	SCENE->Update();
	UI->Update();

	if (GAME->m_isPause) return;

	if (KEYDOWN(VK_F4)) {
		DEBUG_LOG("메뉴로 이동\n");
		SCENE->ChangeScene("TitleScene", "None", 0.f);
	}
	if (KEYDOWN(VK_F5)) {
		DEBUG_LOG("스테이지1로 이동\n");
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
	OBJECT->Render();
	EFFECT->Render();
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
