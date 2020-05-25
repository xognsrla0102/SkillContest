#pragma once
class cTimer
{
private:
	friend class cAnimation;
private:
	FLOAT m_time;
	FLOAT m_curTime;
	function<void()> m_func;
	BOOL m_loop;
public:
	cTimer(FLOAT time, function<void()> func, BOOL loop = FALSE);
	~cTimer() {}
	void Update();
};