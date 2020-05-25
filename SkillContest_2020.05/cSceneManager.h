#pragma once
#include "cSingleton.hpp"

class cScene;
class cSceneManager : public cSingleton<cSceneManager>
{
private:
	cScene* m_now;
	cScene* m_next;
	map<string, cScene*> m_scenes;

	cTexture* m_white;

	BOOL m_isFadeIn = FALSE, m_isFadeInEnd = FALSE;
	BOOL m_isFadeOut = FALSE, m_isFadeOutEnd = FALSE;
	BOOL m_isChangeScene = FALSE;
	FLOAT m_changeSpeed = 20.f;
public:
	cSceneManager();
	virtual ~cSceneManager();

	void AddScene(const string& key, cScene* scenePtr);
	void ChangeScene(const string& key);

	void Update();
	void Render();

	void FadeIn();
	void FadeOut();

	void ChangeSceneEffect(FLOAT changeSpeed = 20.f);
};

#define SCENE cSceneManager::GetInst()