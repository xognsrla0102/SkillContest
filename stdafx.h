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
constexpr int GAMESIZEX = 300;
constexpr int GAMESIZEY = 570;

//오브젝트 태그는 렌더링 순서에 의존적임. 순서 변동하면 렌더 순서가 바뀜
enum TAGS {
	ENEMY,
	BULLET,
	ITEM,
	PLAYER,
	TAG_END,
};

#include "SDKsound.h"
#include "cAnimation.h"
#include "cEffect.h"
#include "cTexture.h"
#include "cImage.h"
#include "cMultiTexture.h"
#include "cObject.h"
#include "cImageManager.h"
#include "cEffectManager.h"
#include "cSceneManager.h"
#include "cInputManager.h"
#include "cSoundManager.h"
#include "cFontManager.h"
#include "cCameraManager.h"
#include "cGameManager.h"
#include "cObjectManager.h"
#include "cUIManager.h"

template<typename T>
void Lerp(T& pOut, const T& pV1, const T& pV2, double s) {
	pOut = pOut + (pV2 - pV1) * s * GAME->TIME_SCALE;
}

void DEBUG_LOG(LPCSTR fmt, ...);

#define D_TIME DXUTGetElapsedTime() * GAME->TIME_SCALE
#define DEVICE DXUTGetD3D9Device()