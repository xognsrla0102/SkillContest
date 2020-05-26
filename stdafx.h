#pragma once
#pragma comment(lib, "dsound.lib")

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
#include <ctime>
using namespace std;

using VEC2   = D3DXVECTOR2;
using VEC3   = D3DXVECTOR3;
using VEC4   = D3DXVECTOR4;
using MATRIX = D3DXMATRIXA16;

constexpr int WINSIZEX = 1280;
constexpr int WINSIZEY = 720;

void DEBUG_LOG(LPCSTR fmt, ...);

#include "SDKsound.h"
#include "cAnimation.h"
#include "cTexture.h"
#include "cMultiTexture.h"
#include "cImage.h"
#include "cImageManager.h"
#include "cSceneManager.h"
#include "cInputManager.h"
#include "cSoundManager.h"
#include "cFontManager.h"
#include "cCameraManager.h"
#include "cGameManager.h"

#define D_TIME DXUTGetElapsedTime() * GAME->TIME_SCALE
#define DEVICE DXUTGetD3D9Device()