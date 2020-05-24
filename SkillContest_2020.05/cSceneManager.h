#pragma once
#include "cSingleton.hpp"

class cScene;
class cSceneManager : public cSingleton<cSceneManager>
{
private:
	cScene* m_now;
	cScene* m_next;
	map<string, cScene*> m_scenes;

	void Release();
public:
	cSceneManager();
	virtual ~cSceneManager();

	void AddScene(const string& key, cScene* scenePtr);
	cScene* ChangeScene(const string& key);

	void Update();
	void Render();
};

#define SCENE cSceneManager::GetInst()