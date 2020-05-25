#include "DXUT.h"
#include "cScene.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
	: m_now(nullptr), m_next(nullptr)
{
	IMAGE->AddTexture("ChangeSceneEffect", "resources/image/scenechange/white.png");
	m_white = IMAGE->FindTexture("ChangeSceneEffect");
	m_white->m_a = 0.f;
	m_white->SetNowRGB();
}

cSceneManager::~cSceneManager()
{
	if (m_now) m_now->Release();
	for (auto iter : m_scenes)
		SAFE_DELETE(iter.second);
	m_scenes.clear();
}

void cSceneManager::AddScene(const string& key, cScene* scenePtr)
{
	if (!scenePtr) {
		DEBUG_LOG("�� �����Ͱ� �����ϴ�.\n");
		return;
	}
	if (m_scenes.find(key) != m_scenes.end()) {
		DEBUG_LOG("%s ���� �ֽ��ϴ�.\n", key.c_str());
		return;
	}
	m_scenes[key] = scenePtr;
	DEBUG_LOG("%s �� �����Ϸ�.\n", key.c_str());
}

void cSceneManager::ChangeScene(const string& key)
{
	if (m_scenes.find(key) == m_scenes.end()) {
		DEBUG_LOG("%s ���� �����ϴ�.", key.c_str());
		return;
	}
	m_next = m_scenes.find(key)->second;
}

void cSceneManager::Update()
{
	if (m_isChangeScene) {
		m_isChangeScene = FALSE;
		m_isFadeOut = TRUE;
	}

	if (m_isFadeOut) {
		FadeOut();
		return;
	}

	if ((!m_now && m_next) || (m_next && m_isFadeOutEnd) ) {

		if (m_now) m_now->Release();
		m_now = m_next;
		m_next = nullptr;
		m_now->Init();

		m_isFadeOutEnd = FALSE;
		m_isFadeIn = TRUE;
	}

	if (m_isFadeIn) {
		FadeIn();
		if (m_isFadeInEnd) {
			m_isFadeInEnd = FALSE;
		}
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

	IMAGE->Render(m_white, VEC2(0, 0), VEC2(1, 1), 0.f, FALSE, m_white->m_color);
}

//���� ��Ÿ��
void cSceneManager::FadeIn()
{
	if (m_white->m_a < m_changeSpeed) {
		m_isFadeIn = FALSE;
		m_isFadeInEnd = TRUE;

		m_white->m_a = 0;
	}
	else {
		m_white->m_a -= m_changeSpeed;
	}
	m_white->SetNowRGB();
}

//���� ��ο���
void cSceneManager::FadeOut()
{
	if (m_white->m_a > 255 - m_changeSpeed) {
		m_isFadeOut = FALSE;
		m_isFadeOutEnd = TRUE;
		m_white->m_a = 255;
	}
	else {
		m_white->m_a += m_changeSpeed;
	}
	m_white->SetNowRGB();
}

void cSceneManager::ChangeSceneEffect(FLOAT changeSpeed)
{
	m_changeSpeed = changeSpeed;
	m_isChangeScene = TRUE;
}
