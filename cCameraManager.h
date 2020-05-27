#pragma once
#include "cSingleton.hpp"

class cCameraManager : public cSingleton<cCameraManager>
{
private:
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
	FLOAT start = 0;
public:
	VEC2 m_pos = VEC2(0, 0);
	FLOAT m_size = 1.f;
	FLOAT m_delay = 0.03;
	BOOL m_isShake = FALSE;
	INT m_accel = 1;
	INT m_velocity = 1;
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