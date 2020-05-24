#pragma once
#include "cSingleton.hpp"

class cInput;
class cInputManager : public cSingleton<cInputManager>
{
private:
	BYTE oldKey[256] = { 0 };
	BYTE nowKey[256] = { 0 };

	cInput* keyboard = nullptr;
public:
	cInputManager();
	virtual ~cInputManager();

	void Update();

	BOOL KeyDown(BYTE key);
	BOOL KeyUp(BYTE key);
	BOOL KeyPress(BYTE key);
};

#define INPUT cInputManager::GetInst()

#define KEYDOWN(key) INPUT->KeyDown(key)
#define KEYUP(key) INPUT->KeyUp(key)
#define KEYPRESS(key) INPUT->KeyPress(key)