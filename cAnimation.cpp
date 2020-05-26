#include "DXUT.h"
#include "cTimer.h"
#include "cAnimation.h"

cAnimation::cAnimation(float delay, int endFrame, bool isOnce)
	: m_endFrame(endFrame)
{
	m_timer = new cTimer(delay);
}

cAnimation::~cAnimation()
{
	SAFE_DELETE(m_timer);
}

void cAnimation::Update()
{
	if (m_timer->Update()) {
		if (m_nowFrame == m_endFrame - 1) {
			if (m_isOnce == FALSE)
				m_nowFrame = 0;
		}
		else {
			m_nowFrame++;
		}
	}
}