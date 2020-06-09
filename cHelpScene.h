#pragma once
#include "cScene.h"
class cHelpScene : public cScene
{
private:
	cImage* m_bg;
public:
	cHelpScene();
	virtual ~cHelpScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

