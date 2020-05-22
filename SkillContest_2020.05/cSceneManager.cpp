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
		DEBUG_LOG("�� �����Ͱ� �����ϴ�.\n");
		return;
	}
	if (m_scenes.find(key) != m_scenes.end()) {
		DEBUG_LOG("���� �̸��� ���� �ֽ��ϴ�.\n");
		return;
	}
	m_scenes[key] = scenePtr;
	DEBUG_LOG("%s �� �����Ϸ�.\n", key);
}

cScene* cSceneManager::ChangeScene(const string& key)
{
	if (m_scenes.find(key) == m_scenes.end()) {
		DEBUG_LOG("ã�� ���� �����ϴ�.");
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
		DEBUG_LOG("���� ����ִ� ���� �����ϴ�.\n");
		return;
	}
	m_now->Update();
}

void cSceneManager::Render()
{
	if (!m_now) {
		DEBUG_LOG("���� ����ִ� ���� �����ϴ�.\n");
		return;
	}
	m_now->Render();
}
