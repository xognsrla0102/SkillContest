#pragma once
#include "cScene.h"
class cGameOverScene : public cScene
{
private:
	cImage* m_bg;
public:
	cGameOverScene();
	virtual ~cGameOverScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

