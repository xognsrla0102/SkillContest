#include "DXUT.h"
#include "math.h"

float DistPoint(VEC2 a, VEC2 b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
