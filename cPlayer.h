#pragma once
#include "cObject.h"
class cPlayer : public cObject
{
private:
	FLOAT m_fireDelay;
	FLOAT m_originSpd;
	FLOAT m_moveSpd;
public:
	cPlayer();
	virtual ~cPlayer();

	virtual void Update() override;
	virtual void Render() override;

	void Init();
	void Release();

	void Move();
};

