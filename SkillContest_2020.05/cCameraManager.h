#pragma once
#include "cSingleton.hpp"

class cCameraManager : public cSingleton<cCameraManager>
{
private:
	D3DXMATRIX m_matView;
	//투영 행렬 처리
	D3DXMATRIX m_matProj;

	VEC2 m_pos = VEC2(0, 0);
	FLOAT m_size = 1.f;
	time_t start;
public:
	BOOL m_isShake = FALSE;
	BOOL m_isPause = FALSE;
	INT m_accel = 1;
	INT m_velocity = 1;
	INT m_delay = 30;
public:
	cCameraManager();
	virtual ~cCameraManager();

	void ResetCamera();
	void Update();
	void SetTransform();

	void ResetSetting();
	void Shake();
};

#define CAMERA cCameraManager::GetInst()