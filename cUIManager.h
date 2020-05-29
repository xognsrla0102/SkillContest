#pragma once
#include "cSingleton.hpp"

class cUIManager : public cSingleton<cUIManager>
{
private:
	cImage* m_ingameBG;
public:
	cUIManager();
	virtual ~cUIManager();

	void Init();
	void Render();
};

#define UI cUIManager::GetInst()