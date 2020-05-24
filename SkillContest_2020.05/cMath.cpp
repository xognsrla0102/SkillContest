#include "DXUT.h"
#include "cMath.h"

using namespace Math;

INT Math::sign(FLOAT value)
{
	if (value > 0) return 1;
	else if (value < 0) return -1;
	return 0;
}

BOOL Math::CheckCollBoxBox(RECT thisRect, RECT otherRect)
{
	RECT rt;
	if(IntersectRect(&rt, &thisRect, &otherRect))
		return TRUE;
	return FALSE;
}

BOOL Math::CheckCollCirCir(VEC2 thisPos, FLOAT thisRad, VEC2 otherPos, FLOAT otherRad)
{
	if (Math::PointDistance(thisPos, otherPos) < thisRad + otherRad)
		return TRUE;
	return FALSE;
}

BOOL Math::CheckCollBoxCir(VEC2 thisPos, RECT thisRect, VEC2 otherPos, FLOAT otherRad)
{
	VEC2 closest;
	if (otherPos.x <= thisPos.x + thisRect.left)
		closest.x = thisPos.x + thisRect.left;
	else if (otherPos.x >= thisPos.x + thisRect.right)
		closest.x = thisPos.x + thisRect.right;
	else closest.x = otherPos.x;

	if (otherPos.y <= thisPos.y + thisRect.top)
		closest.y = thisPos.y + thisRect.top;
	else if (otherPos.y >= thisPos.y + thisRect.bottom)
		closest.y = thisPos.y + thisRect.bottom;
	else closest.y = otherPos.y;

	if (Math::PointDistance(closest, otherPos) < otherRad)
		return TRUE;
	return FALSE;
}

FLOAT Math::PointDistance(VEC2 pos1, VEC2 pos2)
{
	FLOAT x = pos2.x - pos1.x;
	FLOAT y = pos2.y - pos1.y;
	FLOAT dir = atan2(y, x);

	return abs(x * cos(dir)) + abs(y * sin(dir));
}

cObject* Math::Nearest(VEC2 pos, CHAR name)
{
	list<cObject*> objs = OBJECT->Find(string(&name));
	if (objs.size() == 0) return nullptr;
	objs.sort([&](cObject* pPrev, cObject* pNext)->BOOL { return 
		Math::PointDistance(pos, pPrev->GetPos()) < 
		Math::PointDistance(pos, pNext->GetPos()); 
	});
	return objs.front();
}

cObject* Math::Nearest(VEC2 pos, INT objTag)
{
	list<cObject*> objs = OBJECT->Find((OBJ_Tag)objTag);
	if (objs.size() == 0) return nullptr;
	objs.sort([&](cObject* pPrev, cObject* pNext)->BOOL { return
		Math::PointDistance(pos, pPrev->GetPos()) <
		Math::PointDistance(pos, pNext->GetPos());
		});
	return objs.front();
}
