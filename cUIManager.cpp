#include "DXUT.h"
#include "cUI.h"
#include "cIngameUI.h"
#include "cUIManager.h"

cUIManager::cUIManager()
{
	m_UIs["IngameSceneUI"] = new cIngameUI;
}

cUIManager::~cUIManager()
{
	for (auto iter : m_UIs)
		SAFE_DELETE(iter.second);
	m_UIs.clear();
}

void cUIManager::Init()
{
	//로딩 후 각종 UI속 이미지 초기화
	for (auto iter : m_UIs)
		iter.second->Init();
}

void cUIManager::Render()
{
	const string sceneName = SCENE->GetNowSceneKey();

	map<string, cUI*>::iterator find;

	if (sceneName == "LoadScene")
		return;
	else if (sceneName == "TitleScene")
		return;
	else if (sceneName == "StageOneScene" || sceneName == "StageTwoScene")
		find = m_UIs.find("IngameSceneUI");
	find->second->Render();
}
