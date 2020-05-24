#pragma once
#include "cComponent.h"

class cAnimator;
class cAnimation : public cComponent
{
private:
	friend class cObject;
private:
	map<string, cAnimator*> m_animators;
	cAnimator* m_currentAnimator = nullptr;
	FLOAT m_playSpeed;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cAnimation(cObject* obj);
	~cAnimation();

	string GetCurrentAnimatorKey();

	FLOAT GetPlaySpeed();
	void SetPlaySpeed(FLOAT speed);

	INT GetCurrentFrame();
	void SetCurrentFrame(INT frame);

	BOOL GetPaused();
	void SetPaused(BOOL pause);

	cAnimator* FindAnimator(string key);
	cAnimator* AddAnimator(string key, string imageKey, FLOAT delay, BOOL once = FALSE);

	void SetCurrentAnimator(string key);
};

