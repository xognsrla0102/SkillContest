#pragma once
#include "cScene.h"
class cLoadScene : public cScene
{
private:
public:
	cLoadScene();
	virtual ~cLoadScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

