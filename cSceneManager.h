#pragma once
#include "cSingleton.hpp"

class cScene;
class cSceneManager : public cSingleton<cSceneManager>
{
private:
	cScene* m_now = nullptr;
	cScene* m_next = nullptr;
	map<string, cScene*> m_scenes;


	BOOL m_isFadeIn = FALSE;
	BOOL m_isFadeOut = FALSE;

	BOOL m_isFadeChange = FALSE;
	BOOL m_isPlaneChange = FALSE;
	
	FLOAT m_changeSpeed = 20.f;
public:
	BOOL m_isSceneChange = FALSE;
	cImage* m_white;
	cImage* m_plane;
public:
	cSceneManager();
	virtual ~cSceneManager();

	void AddScene(const string& key, cScene* scenePtr);
	void ChangeScene(const string& key, string changeName, FLOAT changeSpeed);

	void Update();
	void Render();

	bool FadeIn();
	bool FadeOut();

	void FadeSceneChange();
	void PlaneSceneChange();

	string GetNowSceneKey();
};

#define SCENE cSceneManager::GetInst()