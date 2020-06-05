#pragma once
class cTimer
{
public:
	FLOAT m_start = 9999;
	FLOAT m_delay = 0;
public:
	cTimer(FLOAT delay);
	~cTimer() {}

	BOOL Update();
};

