#pragma once
class cTimer
{
public:
	FLOAT m_start = 0;
	FLOAT m_delay = 0;
public:
	cTimer(FLOAT delay);
	~cTimer() {}

	BOOL Update();
};

