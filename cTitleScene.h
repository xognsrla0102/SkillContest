#pragma once
#include "cScene.h"
class cTitleScene : public cScene
{
private:
	cImage* m_bg = nullptr;
public:
	cTitleScene();
	virtual ~cTitleScene();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

