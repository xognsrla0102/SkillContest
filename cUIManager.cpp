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
	//�ε� �� ���� UI�� �̹��� �ʱ�ȭ
	for (auto iter : m_UIs)
		iter.second->Init();
}

void cUIManager::Render()
{
	const string sceneName = SCENE->GetNowSceneKey();

	map<string, cUI*>::iterator find;

	if (sceneName == "LoadScene") return;
	else if (sceneName == "TitleScene") {
		DRAW_FLOAT_SIZE(to_string(DXUTGetFPS()), VEC2(1130, 680), 5, 22, 20, VEC2(0.5, 0.5));
		return;
	}
	else if (sceneName == "StageOneScene" || sceneName == "StageTwoScene")
		find = m_UIs.find("IngameSceneUI");

	find->second->Render();
	
	DRAW_FLOAT_SIZE(to_string(DXUTGetFPS()), VEC2(1130, 680), 5, 22, 20, VEC2(0.5, 0.5));
}
