#include "DXUT.h"
#include "cScene.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
{
	IMAGE->AddTexture("ChangeSceneEffect", "resources/image/scenechange/white.png");
	
	m_white = new cImage;
	m_white->m_text = IMAGE->FindTexture("ChangeSceneEffect");
	m_white->m_a = 0.f;
	m_white->SetNowRGB();
}

cSceneManager::~cSceneManager()
{
	SAFE_DELETE(m_white);

	if (m_now) m_now->Release();
	for (auto iter : m_scenes)
		SAFE_DELETE(iter.second);
	m_scenes.clear();
}

void cSceneManager::AddScene(const string& key, cScene* scenePtr)
{
	if (!scenePtr) {
		DEBUG_LOG("씬 포인터가 없습니다.\n");
		return;
	}
	if (m_scenes.find(key) != m_scenes.end()) {
		DEBUG_LOG("%s 씬이 있습니다.\n", key.c_str());
		return;
	}
	m_scenes[key] = scenePtr;
	DEBUG_LOG("%s 씬 생성완료.\n", key.c_str());
}

void cSceneManager::ChangeScene(const string& key)
{
	if (m_scenes.find(key) == m_scenes.end()) {
		DEBUG_LOG("%s 씬이 없습니다.", key.c_str());
		return;
	}

	if (m_now) m_now->Release();
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

	if (m_next) {
		m_now = m_next;
		m_next = nullptr;
		m_now->Init();
		m_isFadeIn = TRUE;
	}

	if (m_isFadeIn) FadeIn();

	if (!m_now) return;
	m_now->Update();
}

void cSceneManager::Render()
{
	if (!m_now) return;
	m_now->Render();

	IMAGE->Render(m_white->m_text, VEC2(0, 0), VEC2(1, 1), 0.f, FALSE, m_white->m_color);
}

//점점 나타남
void cSceneManager::FadeIn()
{
	if (m_white->m_a < m_changeSpeed) {
		m_isFadeIn = FALSE;
		m_white->m_a = 0;
	}
	else {
		m_white->m_a -= m_changeSpeed;
	}
	m_white->SetNowRGB();
}

//점점 어두워짐
void cSceneManager::FadeOut()
{
	if (m_white->m_a > 255 - m_changeSpeed) {
		m_isFadeOut = FALSE;
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
