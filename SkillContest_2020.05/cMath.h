#pragma once

class cObject;

namespace Math
{
	INT sign(FLOAT value);

	BOOL CheckCollBoxBox(RECT thisRect, RECT otherRect);
	BOOL CheckCollCirCir(VEC2 thisPos, FLOAT thisRad, VEC2 otherPos, FLOAT otherRad);
	BOOL CheckCollBoxCir(VEC2 thisPos, RECT thisRect, VEC2 otherPos, FLOAT otherRad);

	FLOAT PointDistance(VEC2 pos1, VEC2 pos2);

	cObject* Nearest(VEC2 pos, CHAR name);
	cObject* Nearest(VEC2 pos, INT objTag);
}
