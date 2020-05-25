#pragma once
#include "cScene.h"
class cStageOne : public cScene
{
private:
	cTexture* m_bg1 = nullptr, *m_bg2 = nullptr;
	VEC2 bgPos1 = VEC2(0, 0), bgPos2 = VEC2(0, 0);
public:
	cStageOne();
	virtual ~cStageOne();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};
