#pragma once
#include "cObject.h"

struct cMotionInfo {
	VEC2 m_motionPos;
	D3DXCOLOR m_color;

	cMotionInfo(VEC2 pos) : m_motionPos(pos) {}
};

class cPlayer : public cObject
{
private:
	vector<cMotionInfo*> m_motionInfo;
	cTimer* m_fire;
	cTimer* m_motion;
	FLOAT m_originSpd;
	FLOAT m_moveSpd;
	bool m_canFire = false;
public:
	int m_nowWeapon = 0;
public:
	cPlayer();
	virtual ~cPlayer();

	virtual void Update() override;
	virtual void Render() override;

	void Init();
	void Release();

	void ChangeWeapon();

	void Move();
	void Fire();

	void MotionBlur();
};

