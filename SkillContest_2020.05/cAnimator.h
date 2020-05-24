#pragma once

class cTimer;
class cTexture;

class cAnimator : private cComponent
{
	friend class cObject;
	friend class cAnimation;
private:
	vector<cTexture*> m_images;
	INT m_currentFrame;
	cTimer* m_timer = nullptr;
	string m_key;
	BOOL m_once;
	BOOL m_pause;
	FLOAT m_delay;
	FLOAT m_defaultDelay;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cAnimator(cObject* obj, string imageKey, FLOAT delay, BOOL once = FALSE);
	~cAnimator();
};

