#include "DXUT.h"
#include "cLoadScene.h"
#include "cMainProc.h"

cMainProc::cMainProc()
{
	srand(time(NULL));

	SCENE->AddScene("LoadScene", new cLoadScene);
	SCENE->ChangeScene("LoadScene");
}

cMainProc::~cMainProc()
{
	EFFECT->ReleaseInst();
	INPUT->ReleaseInst();
	SCENE->ReleaseInst();
	SOUND->ReleaseInst();
	IMAGE->ReleaseInst();
	CAMERA->ReleaseInst();
	FONT->ReleaseInst();
	GAME->ReleaseInst();
}

void cMainProc::Update()
{
	CAMERA->Update();
	INPUT->Update();
	EFFECT->Update();
	SCENE->Update();
	FONT->Update();
}

void cMainProc::Render()
{
	CAMERA->SetTransform();

	IMAGE->Begin(false);

	SCENE->Render();
	EFFECT->Render();
	FONT->Render();

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
