#pragma once
#include "cSingleton.hpp"

constexpr int KEY_MAX = 256;

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
	BOOL IsKeyDown(INT key) { return (m_nowKey[key]  == true  && m_pastKey[key] == false); }
	BOOL IsKeyPress(INT key) { return (m_nowKey[key] == true  && m_pastKey[key] == true); }
	BOOL IsKeyUp(INT key) { return (m_nowKey[key]    == false && m_pastKey[key] == true); }
	VEC2 GetMousePos() { return m_mouse; }
};

#define	INPUT cInputManager::GetInst()

#define KEYDOWN(key) INPUT->IsKeyDown(key)
#define KEYPRESS(key) INPUT->IsKeyPress(key)
#define KEYUP(key) INPUT->IsKeyUp(key)