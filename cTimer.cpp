#include "DXUT.h"
#include "cTimer.h"

cTimer::cTimer(FLOAT delay) : m_delay(delay)
{
}

BOOL cTimer::Update()
{
	m_start += D_TIME;
	if (m_start > m_delay) {
		m_start = 0.f;
		return TRUE;
	}
	return FALSE;
}
