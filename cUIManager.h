#pragma once
#include "cSingleton.hpp"

class cUI;
class cUIManager : public cSingleton<cUIManager>
{
private:
	map<string, cUI*> m_UIs;
public:
	cUIManager();
	virtual ~cUIManager();

	void Init();
	void Render();
};

#define UI cUIManager::GetInst()