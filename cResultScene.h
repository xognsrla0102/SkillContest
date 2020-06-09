#pragma once
#include "cScene.h"
class cResultScene : public cScene
{
private:
	string m_scorePrint;
	cImage* m_bg;
	float m_nowYourScore;
public:
	cResultScene();
	virtual ~cResultScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

