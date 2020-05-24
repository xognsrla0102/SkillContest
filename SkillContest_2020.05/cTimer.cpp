#include "DXUT.h"
#include "cTimer.h"

cTimer::cTimer(FLOAT time, function<void()> func, BOOL loop)
	:m_time(time), m_func(func), m_loop(loop)
{
	m_curTime = 0;
}

void cTimer::Update()
{
	m_curTime++;
	if (m_curTime >= m_time)
	{
		m_func();
		if (m_loop) m_curTime = 0;
		else delete this;
	}
}