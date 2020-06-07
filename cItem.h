#pragma once
#include "cObject.h"
class cItem : public cObject
{
private:
	string m_key;
	VEC2 m_endPos;
	BOOL m_isEndPos = FALSE;
	FLOAT m_accel = 0.f;
public:
	cItem(string key, VEC2 pos, VEC2 endPos);
	virtual ~cItem();

	virtual void Update() override;
	virtual void Render() override;

	void Collision();
};

