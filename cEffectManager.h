#pragma once
#include "cSingleton.hpp"

class cEffect;
class cEffectManager : public cSingleton<cEffectManager>
{
private:
	vector<cEffect*> m_efts;
public:
	cEffectManager();
	virtual ~cEffectManager();

	void AddEffect(cEffect* eftPtr);

	void Update();
	void Render();

	void Reset();
};

#define EFFECT cEffectManager::GetInst()