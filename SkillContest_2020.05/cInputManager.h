#pragma once
#include "cSingleton.hpp"

constexpr INT KEY_MAX = 256;

class cInputManager : public cSingleton<cInputManager>
{
public:
	BOOL m_nowKey[KEY_MAX];
	BOOL m_pastKey[KEY_MAX];
	VEC2 m_mouse;
private:
	vector<cTexture*> m_mouseTexture;
	vector<FLOAT>	  m_mouseRotate;
public:
	cInputManager();
	~cInputManager();
public:
	void Update();
	void Render();
public:
	BOOL IsKeyDown(INT key)  { return (m_nowKey[key] && m_pastKey[key] == false); }
	BOOL IsKeyPress(INT key) { return (m_nowKey[key] && m_pastKey[key]); }
	BOOL IsKeyUp(INT key) { return (m_nowKey[key] == false && m_pastKey[key]); }
	VEC2 GetMousePos() { return m_mouse; }
public:
	FLOAT GetHorizontal();
	FLOAT GetVertical();
};


#define	INPUTMANAGER cInputManager::GetInst()

#define KEYDOWN(key) INPUTMANAGER->IsKeyDown(key)
#define KEYPRESS(key) INPUTMANAGER->IsKeyPress(key)
#define KEYUP(key) INPUTMANAGER->IsKeyUp(key)