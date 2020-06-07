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
	cTimer* m_motion;
	cTimer* m_boostCool;

	cImage* m_boostBar;

	cAnimation* m_qAni;

	FLOAT m_originSpd;
	FLOAT m_moveSpd;

	FLOAT m_boostTime;
	FLOAT m_damageTime;

	FLOAT m_alpha;

	bool m_isBoostCool;
	bool m_canFire;
public:
	string m_stealTanName;

	cTimer* m_fire = nullptr;

	//총알 딜레이[무기];
	float m_fireDelay[3] = { 0 };

	//무기 공격력[무기];
	float m_atk[3] = { 0 };

	P_STATUS m_status;

	bool m_isBoost;
	bool m_isDamaged;

	bool m_isSteal;

	bool m_isQ;
	bool m_isW;

	float m_Qtime;
	float m_Wtime;

	int m_hp;
	int m_hpMax;

	int m_nowWeapon;
public:
	cPlayer();
	virtual ~cPlayer();

	virtual void Update() override;
	virtual void Render() override;
	void OnCollision(cObject* other);

	void Init();
	void Release();

	void Dead();

	void ChangeWeapon();

	void Boost();
	void Move();
	void Fire();

	void Skill();

	void MotionBlur();
};

