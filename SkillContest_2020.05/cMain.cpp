#include "DXUT.h"
#include "cLoadScene.h"
#include "cMain.h"

cMain::cMain()
{
	srand(time(NULL));

	SCENE->AddScene("LoadScene", new cLoadScene);
	SCENE->ChangeScene("LoadScene");
}

cMain::~cMain()
{
	INPUTMANAGER->ReleaseInst();
	SCENE->ReleaseInst();
	OBJECT->ReleaseInst();
	SOUND->ReleaseInst();
	IMAGE->ReleaseInst();
	GAME->ReleaseInst();
	CAMERA->ReleaseInst();	
}

void cMain::Update()
{
	CAMERA->Update();
	INPUTMANAGER->Update();
	OBJECT->Update();
	SCENE->Update();
}

void cMain::Render()
{
	CAMERA->SetTransform();
	
	IMAGE->Begin(FALSE);
	
	SCENE->Render();

	OBJECT->Render();
	
	IMAGE->End();
}

void cMain::ResetDevice()
{
	IMAGE->ResetDevice();
}

void cMain::LostDevice()
{
	CAMERA->ResetCamera();
	IMAGE->LostDevice();
}
