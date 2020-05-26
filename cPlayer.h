#pragma once
#include "cObject.h"
class cPlayer : public cObject
{
private:
	FLOAT m_fireDelay;
	FLOAT m_moveSpd;

public:
	cPlayer(cTexture* text);
	virtual ~cPlayer();

	virtual void Update() override;
	virtual void Render() override;

	void Init();
	void Release();
};

