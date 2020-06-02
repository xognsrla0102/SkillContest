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

void cSceneManager::ChangeScene(const string& key, string changeName, FLOAT changeSpeed)
{
	if (m_scenes.find(key) == m_scenes.end()) {
		DEBUG_LOG("%s ���� �����ϴ�.", key.c_str());
		return;
	}
	m_next = m_scenes.find(key)->second;

	m_changeSpeed = changeSpeed;

	if (changeName == "Fade") {
		m_isFadeChange = true;
		m_isFadeOut = true;
	}
	else if (changeName == "Plane")
		m_isPlaneChange = true;
}

void cSceneManager::Update()
{
	if ((!(m_isFadeChange || m_isPlaneChange) && m_next) ||
		(m_next && m_isFadeIn && m_white->m_a > 240.f)
		) {
		SAFE_RELEASE(m_now);
		m_now = m_next;
		m_next = nullptr;
		m_now->Init();
	}

	if (m_isFadeChange) FadeSceneChange();
	else if (m_isPlaneChange) PlaneSceneChange();

	if (m_now) m_now->Update();
}

void cSceneManager::Render()
{
	if (m_now) m_now->Render();

	if (m_isFadeChange)
		IMAGE->Render(m_white->m_text, VEC2(0, 0), VEC2(1, 1), 0.f, FALSE, m_white->m_color);
}

//���� ��Ÿ��
bool cSceneManager::FadeIn()
{
	if (m_white->m_a < m_changeSpeed) {
		m_white->m_a = 0;
		m_white->SetNowRGB();
		return true;
	}
	else {
		m_white->m_a -= m_changeSpeed;
		m_white->SetNowRGB();
		return false;
	}
}

//���� ��ο���
bool cSceneManager::FadeOut()
{
	if (m_white->m_a > 255 - m_changeSpeed) {
		m_white->m_a = 255;
		m_white->SetNowRGB();
		return true;
	}
	else {
		m_white->m_a += m_changeSpeed;
		m_white->SetNowRGB();
		return false;
	}
}

void cSceneManager::FadeSceneChange()
{
	//���̵� �ƿ� ���� �ϰ� ���̵� ���� �ؾ� �Ѵ�.
	if (m_isFadeOut) {
		if (FadeOut()) {
			m_isFadeOut = false;
			m_isFadeIn = true;
		}
		return;
	}

	if (m_isFadeIn) {
		if (FadeIn()) {
			m_isFadeIn = false;
			m_isFadeChange = false;
		}
	}
}

void cSceneManager::PlaneSceneChange()
{
}

string cSceneManager::GetNowSceneKey()
{
	for (auto iter : m_scenes) {
		if (m_now == iter.second)
			return iter.first;
	}
	return "���� ���� ã�� �� �����ϴ�.\n";
}
