#pragma once
#include "cSingleton.hpp"

class cScene;
class cSceneManager : public cSingleton<cSceneManager>
{
private:
	cScene* m_now = nullptr;
	cScene* m_next = nullptr;
	map<string, cScene*> m_scenes;

	cImage* m_white;

	BOOL m_isFadeIn = FALSE;
	BOOL m_isFadeOut = FALSE;
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