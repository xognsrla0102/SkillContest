#include "DXUT.h"
#include "cUIManager.h"

cUIManager::cUIManager()
{
	m_ingameBG = new cImage;
}

cUIManager::~cUIManager()
{
	SAFE_DELETE(m_ingameBG);
}

void cUIManager::Init()
{
	m_ingameBG->m_text = IMAGE->FindTexture("IngameBGUI");
}

void cUIManager::Render()
{
	string nowSceneKey = SCENE->GetNowSceneKey();

	if (nowSceneKey == "StageOneScene") {
		IMAGE->Render(m_ingameBG->m_text, VEC2(0, 0));
	}
}
