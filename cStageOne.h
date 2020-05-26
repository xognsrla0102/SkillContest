#pragma once
#include "cScene.h"

class cScroolMap;
class cStageOne : public cScene
{
private:
	cScroolMap* m_map;
public:
	cStageOne();
	virtual ~cStageOne();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

