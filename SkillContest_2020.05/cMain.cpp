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
	INPUT->ReleaseInst();
	SCENE->ReleaseInst();
	OBJECT->ReleaseInst();
	SOUND->ReleaseInst();
	IMAGE->ReleaseInst();
	CAMERA->ReleaseInst();
}

void cMain::Update()
{
	CAMERA->Update();
	INPUT->Update();
	SCENE->Update();
}

void cMain::Render()
{
	CAMERA->SetTransform();

	IMAGE->Begin(FALSE);

	SCENE->Render();

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
