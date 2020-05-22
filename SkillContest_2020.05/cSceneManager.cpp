#include "DXUT.h"
//#include "cScene.h"
#include "cSceneManager.h"

void cSceneManager::Release()
{
	if (m_now) m_now->Release();
	for (auto iter : m_scenes)
		SAFE_DELETE(iter.second);
	m_scenes.clear();
}

cSceneManager::cSceneManager()
	: m_now(nullptr), m_next(nullptr)
{
}

cSceneManager::~cSceneManager()
{
	Release();
}

void cSceneManager::AddScene(const string& key, cScene* scenePtr)
{
	if (!scenePtr) {
		DEBUG_LOG("씬 포인터가 없습니다.\n");
		return;
	}
	if (m_scenes.find(key) != m_scenes.end()) {
		DEBUG_LOG("같은 이름의 씬이 있습니다.\n");
		return;
	}
	m_scenes[key] = scenePtr;
	DEBUG_LOG("%s 씬 생성완료.\n", key);
}

cScene* cSceneManager::ChangeScene(const string& key)
{
	if (m_scenes.find(key) == m_scenes.end()) {
		DEBUG_LOG("찾는 씬이 없습니다.");
		return nullptr;
	}
	m_next = m_scenes.find(key)->second;
	return m_next;
}

void cSceneManager::Update()
{
	if (m_next) {
		if (m_now) m_now->Release();
		m_now = m_next;
		m_now->Init();
		m_next = nullptr;
	}

	if (!m_now) {
		DEBUG_LOG("현재 들어있는 씬이 없습니다.\n");
		return;
	}
	m_now->Update();
}

void cSceneManager::Render()
{
	if (!m_now) {
		DEBUG_LOG("현재 들어있는 씬이 없습니다.\n");
		return;
	}
	m_now->Render();
}
