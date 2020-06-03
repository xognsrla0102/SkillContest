#pragma once
#include "cSingleton.hpp"

class cUI;
class cUIManager : public cSingleton<cUIManager>
{
private:
	map<string, cUI*> m_UIs;
	cUI* m_now = nullptr;
	cUI* m_next = nullptr;
public:
	cUIManager();
	virtual ~cUIManager();

	void Init();
	void Update();
	void Render();

	cUI* FindUI(string name);
};

#define UI cUIManager::GetInst()