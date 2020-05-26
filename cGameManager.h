#pragma once
#include "cSingleton.hpp"

class cGameManager : public cSingleton<cGameManager>
{
public:
	float TIME_SCALE = 1.f;
public:
	cGameManager();
	virtual ~cGameManager();


};

#define GAME cGameManager::GetInst()