#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <cstdarg>
using namespace std;

using VEC2 = D3DXVECTOR2;
using VEC3 = D3DXVECTOR3;
using VEC4 = D3DXVECTOR4;

#define D_TIME DXUTGetElapsedTime()
#define DEVICE DXUTGetD3D9Device()

extern BOOL isWindowed;

#ifdef _DEBUG
	#define WINSIZEX 1280
	#define WINSIZEY 720
#else
	#define WINSIZEX 1920
	#define WINSIZEY 1080
#endif

template<typename T>
void Lerp(T& start, T end, FLOAT t) {
	start = start + t * (end - start);
}

void DEBUG_LOG(LPCSTR fmt, ...);