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
constexpr int GAMESIZEX = 600;
constexpr int GAMESIZEY = 570;

#define GX(x) (WINSIZEX / 2 - GAMESIZEX / 2 + x)
#define GY(y) (WINSIZEY / 2 - GAMESIZEY / 2 + y)
#define GXY(x, y) (VEC2(WINSIZEX / 2 - GAMESIZEX / 2 + x, WINSIZEY / 2 - GAMESIZEY / 2 + y))

//오브젝트 태그는 렌더링 순서에 의존적임. 순서 변동하면 렌더 순서가 바뀜
enum TAGS {
	ENEMY,
	BULLET,
	PLAYER,
	ITEM,
	TAG_END,
};

enum P_STATUS {
	P_IDLE,
	P_LEFT,
	P_RIGHT,
};

#include "SDKsound.h"
#include "math.h"
#include "collision.h"
#include "cAnimation.h"
#include "cEffect.h"
#include "cTexture.h"
#include "cImage.h"
#include "cTimer.h"
#include "cMultiTexture.h"
#include "cObject.h"
#include "cPlayer.h"
#include "cButton.h"
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
#include "cEnemy.h"
#include "cEnemyManager.h"
#include "cBullet.h"
#include "cBulletManager.h"

template<typename T>
void Lerp(T& pV1, const T& pV2, double s) {
	pV1 = pV1 + (pV2 - pV1) * s * GAME->TIME_SCALE;
}

void DEBUG_LOG(LPCSTR fmt, ...);

#define D_TIME DXUTGetElapsedTime() * GAME->TIME_SCALE
#define DEVICE DXUTGetD3D9Device()