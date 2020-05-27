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
	OBJECT->ReleaseInst();
}

void cMainProc::Update()
{
	INPUT->Update();
	GAME->Update();
	CAMERA->Update();
	SCENE->Update();
	OBJECT->Update();
	EFFECT->Update();
	FONT->Update();
}

void cMainProc::Render()
{
	CAMERA->SetTransform();

	IMAGE->Begin(false);

	SCENE->Render();
	OBJECT->Render();
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
