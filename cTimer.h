#pragma once
class cTimer
{
private:
	FLOAT m_start = 0;
public:
	FLOAT m_delay = 0;
public:
	cTimer(FLOAT delay);
	~cTimer() {}

	BOOL Update();
};

