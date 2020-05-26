#include "DXUT.h"
#include "cInputManager.h"

cInputManager::cInputManager()
{
	memset(m_pastKey, FALSE, sizeof(m_pastKey));
	memset(m_nowKey, FALSE, sizeof(m_nowKey));

	//mouseTexture.push_back(Resources->LoadTexture("UI/Mouse/Mouse1.png"));
	//mouseTexture.push_back(Resources->LoadTexture("UI/Mouse/Mouse2.png"));
	//mouseTexture.push_back(Resources->LoadTexture("UI/Mouse/Mouse3.png"));

	//for (int i = 0; i < 3; i++)
	//	mouseRotate.push_back(0);
}

cInputManager::~cInputManager()
{
}

void cInputManager::Update()
{
	memcpy(m_pastKey, m_nowKey, sizeof(m_nowKey));

	for (INT i = 0; i < KEY_MAX; ++i) {
		if (GetAsyncKeyState(i)) m_nowKey[i] = true;
		else m_nowKey[i] = false;
	}

	/*POINT point;

	GetCursorPos(&point);
	ScreenToClient(DXUTGetHWND(), &point);

	m_mouse.x = point.x;
	m_mouse.y = point.y;*/

	/*m_mouseRotate[1] += 100 * ELTime;
	m_mouseRotate[2] -= 100 * ELTime;*/
}

void cInputManager::Render()
{
	/*for (int i = 0; i < mouseTexture.size(); i++)
		RENDERMANAGER->DrawSprite(mouseTexture[i], Vector3(mouse), { 1, 1 }, { 1, 1 }, mouseRotate[i]);*/
}

