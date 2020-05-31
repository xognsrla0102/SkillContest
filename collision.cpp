#include "DXUT.h"
#include "collision.h"

VEC2 GetWidthVector(RECT obj, FLOAT rot)
{
	FLOAT width = obj.right - obj.left;
	VEC2 tmp;
	tmp.x = width * cos(D3DXToRadian(rot)) / 2;
	tmp.y = width * sin(D3DXToRadian(rot)) / 2;

	return tmp;
}

VEC2 GetHeightVector(RECT obj, FLOAT rot)
{
	FLOAT height = obj.bottom - obj.top;
	VEC2 tmp;
	tmp.x = height * cos(D3DXToRadian(rot - 90)) / 2;
	tmp.y = height * sin(D3DXToRadian(rot - 90)) / 2;

	return tmp;
}

BOOL AABB(RECT obj1, RECT obj2) {
	RECT tmp;
	if (IntersectRect(&tmp, &obj1, &obj2) == TRUE) return TRUE;
	return FALSE;
}

BOOL OBB(VEC2 objPos1, VEC2 objPos2, RECT obj1, RECT obj2, FLOAT rot1, FLOAT rot2) {
	VEC2 interval = objPos1 - objPos2;

	VEC2 xV[2], yV[2];
	xV[0] = GetWidthVector(obj1, rot1);
	yV[0] = GetHeightVector(obj1, rot1);
	xV[1] = GetWidthVector(obj2, rot2);
	yV[1] = GetHeightVector(obj2, rot2);

	VEC2 vSA[4];
	D3DXVec2Normalize(&vSA[0], &xV[0]);
	D3DXVec2Normalize(&vSA[1], &yV[0]);
	D3DXVec2Normalize(&vSA[2], &xV[1]);
	D3DXVec2Normalize(&vSA[3], &yV[1]);

	for (size_t i = 0; i < 4; i++) {
		FLOAT d = fabs((D3DXVec2Dot(&vSA[i], &interval)));
		FLOAT r1 =
			fabs(D3DXVec2Dot(&vSA[i], &xV[0]))
			+ fabs(D3DXVec2Dot(&vSA[i], &yV[0]));
		FLOAT r2 =
			fabs(D3DXVec2Dot(&vSA[i], &xV[1]))
			+ fabs(D3DXVec2Dot(&vSA[i], &yV[1]));

		if (r1 + r2 < d) return FALSE;
	}
	return TRUE;
}

BOOL CIRCLE(VEC2 objPos1, VEC2 objPos2, FLOAT r1, FLOAT r2) {
	FLOAT length = D3DXVec2Length(&VEC2(objPos1 - objPos2));
	if (r1 + r2 > length) return TRUE;
	return FALSE;
}
