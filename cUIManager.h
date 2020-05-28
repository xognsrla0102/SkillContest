#pragma once
#include "cSingleton.hpp"

class cUIManager : public cSingleton<cUIManager>
{
public:
	cUIManager();
	virtual ~cUIManager();

	void Render();
};

#define UI cUIManager::GetInst()