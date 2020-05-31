#include "DXUT.h"
#include "cObject.h"

RECT cObject::GetObjCollider()
{
	RECT rt = {
		GetPos().x - GetImg()->m_info.Width / 2 * GetSize().x,
		GetPos().y - GetImg()->m_info.Height / 2 * GetSize().y,
		GetPos().x + GetImg()->m_info.Width / 2 * GetSize().x,
		GetPos().y + GetImg()->m_info.Height / 2 * GetSize().y,
	};
	return rt;
}

bool cObject::OutMapChk(int offset)
{
	RECT world = {
		GX(0 - offset),
		GY(0 - offset),
		GX(GAMESIZEX + offset),
		GY(GAMESIZEY + offset),
	};

	if (!AABB(GetObjCollider(), world)) {
		m_isLive = false;
		return true;
	}
	return false;
}
