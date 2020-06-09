#pragma once
#include "cScene.h"
class cRankScene : public cScene
{
private:
	cImage* m_bg;

public:
	cRankScene();
	virtual ~cRankScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

