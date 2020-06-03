#include "DXUT.h"
#include "cUI.h"
#include "cTitleUI.h"
#include "cIngameUI.h"
#include "cUIManager.h"

cUIManager::cUIManager()
{
	m_UIs["TitleSceneUI"] = new cTitleUI;
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

void cUIManager::Update()
{
	const string sceneName = SCENE->GetNowSceneKey();
	bool isChangeUI = false;
	map<string, cUI*>::iterator find;

	if (sceneName == "TitleScene") {
		find = m_UIs.find("TitleSceneUI");
		isChangeUI = true;
	}
	else if (sceneName == "StageOneScene" || sceneName == "StageTwoScene") {
		find = m_UIs.find("IngameSceneUI");
		isChangeUI = true;
	}
	else {
		if (m_now) m_now->Release();
		m_now = nullptr;
	}

	if(isChangeUI) m_next = find->second;

	if (m_next && m_now != m_next) {
		if(m_now) m_now->Release();
		m_now = m_next;
		m_next = nullptr;
		m_now->Init();
	}

	if (m_now) m_now->Update();
}

void cUIManager::Render()
{
	if(m_now) m_now->Render();
	if(SCENE->GetNowSceneKey() != "LoadScene")
		DRAW_FLOAT_SIZE(to_string(DXUTGetFPS()), VEC2(1130, 680), 5, 22, 20, VEC2(0.5, 0.5));
}

cUI* cUIManager::FindUI(string name)
{
	auto find = m_UIs.find(name);
	if (find == m_UIs.end()) return nullptr;
	return find->second;
}
