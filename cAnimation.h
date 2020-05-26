#pragma once

class cTimer;
class cAnimation
{
private:
	cTimer* m_timer = nullptr;
public:
	int m_nowFrame = 0;
	int m_endFrame;
	bool m_isOnce = FALSE;
public:
	cAnimation(float delay, int m_endFrame, bool isOnce = FALSE);
	~cAnimation();

	void Update();
};

