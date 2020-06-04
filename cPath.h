#pragma once

class cPointInfo {
public:
	BOOL m_isCurve;
	VEC2 m_pos;
	FLOAT m_speed;
	FLOAT m_delay;
public:
	cPointInfo(BOOL isCurve, VEC2 newPos, FLOAT speed, time_t delay = 0)
		: m_isCurve(isCurve), m_pos(newPos), m_speed(speed), m_delay(delay) {}
};

class cPath
{
public:
	vector<cPointInfo> m_endPoint;
	INT   m_nowPos = 0;
	BOOL  m_isLoop = FALSE;
	BOOL  m_isDone = FALSE;
	float m_stay;
public:
	cPath(VEC2 startPos);
	~cPath();

	void AddPoint(VEC2 newPos, FLOAT speed, FLOAT delay);
	void AddCurve(VEC2 nowPos, VEC2 curvePos, VEC2 endPos, FLOAT speed);
	BOOL Update(VEC2 pos, FLOAT moveDist);
};

