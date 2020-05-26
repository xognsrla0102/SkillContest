#include "DXUT.h"
#include "cTimer.h"

cTimer::cTimer(FLOAT delay) : m_delay(delay)
{
}

BOOL cTimer::Update()
{
	m_start += D_TIME;
	if (m_start > m_delay) return TRUE;
	return FALSE;
}
