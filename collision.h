#pragma once

VEC2 GetWidthVector(RECT obj, FLOAT rot);
VEC2 GetHeightVector(RECT obj, FLOAT rot);

BOOL AABB(RECT obj1, RECT obj2);
BOOL OBB(VEC2 objPos1, VEC2 objPos2, RECT obj1, RECT obj2, FLOAT rot1, FLOAT rot2);
BOOL CIRCLE(VEC2 objPos1, VEC2 objPos2, FLOAT r1, FLOAT r2);

