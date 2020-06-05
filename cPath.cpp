#include "DXUT.h"
#include "cPath.h"

cPath::cPath(VEC2 startPos)
{
	AddPoint(startPos, 1, 0);
}

cPath::~cPath()
{
	m_endPoint.clear();
}

void cPath::AddPoint(VEC2 newPos, FLOAT speed, FLOAT delay)
{
	//스피드가 0일 경우 delay만큼 현재 위치 유지
	//딜레이가 0일 경우 스피드만큼 현재 위치 Lerp
	m_endPoint.push_back(cPointInfo(FALSE, newPos, speed, delay));
}

void cPath::AddCurve(VEC2 nowPos, VEC2 curvePos, VEC2 endPos, FLOAT speed) {
	//2차 베지어 곡선을 통해서 움직임을 구현함
	VEC2 p0(nowPos), p1(curvePos), p2(endPos), m0, m1, b;

	m0 = p0, m1 = p1;

	//곡선을 20등분
	for (size_t i = 1; i <= 20; i++) {
		D3DXVec2Lerp(&m0, &p0, &p1, 0.05 * i);
		D3DXVec2Lerp(&m1, &p1, &p2, 0.05 * i);
		D3DXVec2Lerp(&b, &m0, &m1, 0.05 * i);

		m_endPoint.push_back(cPointInfo(TRUE, b, speed, 0));
	}
}

BOOL cPath::Update(VEC2 pos, FLOAT moveDist)
{
	//현재지점과 목표 지점까지의 거리
	FLOAT d = DistPoint(pos, m_endPoint[m_nowPos].m_pos);

	//남은 거리가 이동할 거리보다 작을 때 또는
	//남은 거리가 2.f 미만일 때
	if (d <= moveDist || d < 2.f) {
		//목표 지점이 최종지점일 때
		if (m_nowPos == m_endPoint.size() - 1) {
			if (m_isLoop == TRUE) {
				//m_nowPos++; 이므로 0이 되기 위함
				m_nowPos = 0 - 1;
			}
			else {
				m_isDone = TRUE;
				return FALSE;
			}
		}
		//딜레이가 존재해서 정지한 상태로 딜레이 만큼 유지하거나
		else if (m_endPoint[m_nowPos].m_delay != 0) {
			m_stay += D_TIME;
			if (m_stay < m_endPoint[m_nowPos].m_delay)
				return FALSE;
		}
		m_nowPos++;
		m_stay = 0.f;
		//목표지점으로 이동시켜주는 신호를 보내야 함
		//그 신호를 TRUE를 반환함으로써 구분
		return TRUE;
	}
	else return FALSE;
}
