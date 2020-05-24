#pragma once

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dinput8.lib")

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <dinput.h>
using namespace std;

using VEC2 = D3DXVECTOR2;
using VEC3 = D3DXVECTOR3;
using VEC4 = D3DXVECTOR4;

using MATRIX = D3DXMATRIXA16;

#define D_TIME DXUTGetElapsedTime()
#define DEVICE DXUTGetD3D9Device()

extern BOOL isWindowed;

#ifdef _DEBUG
	constexpr INT winSizeX = 1280;
	constexpr INT winSizeY = 720;
#else
	constexpr INT winSizeX = 1920;
	constexpr INT winSizeY = 1080;
#endif

template<typename T>
void Lerp(T& start, T end, FLOAT t) {
	start = start + t * (end - start);
}

void DEBUG_LOG(LPCSTR fmt, ...);

#include "SDKsound.h"
#include "cMath.h"
#include "cTimer.h"
#include "cObject.h"
#include "cComponent.h"
#include "cAnimator.h"
#include "cAnimator.h"
#include "cBoxCollider.h"
#include "cCircleCollider.h"

#include "cImageManager.h"
#include "cSceneManager.h"
#include "cSoundManager.h"
#include "cCameraManager.h"
#include "cObjectManager.h"
#include "cGameManager.h"
#include "cInputManager.h"