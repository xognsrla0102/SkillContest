#pragma once
#include "cComponent.h"

class cPlayer : public cComponent
{
private:
	friend class cObject;
private:
	cTimer* m_fireDelay = nullptr;
	cTexture* m_bullet = nullptr;
	BOOL m_isHit = FALSE;
	FLOAT m_pSpd = 300.f;

	cObject* AddBullet(VEC2 pos, FLOAT dir, INT dmg, cTexture* text);
	cObject* AddBullet(VEC2 pos, FLOAT dir, INT dmg, cTexture* text, cObject* target);

	void Fire();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cPlayer(cObject* obj);
	~cPlayer();
};

