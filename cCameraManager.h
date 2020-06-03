#pragma once
#include "cSingleton.hpp"

class cCameraManager : public cSingleton<cCameraManager>
{
private:
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
public:
	BOOL m_isShake = FALSE;
	VEC2 m_pos = VEC2(0, 0);
	FLOAT m_size = 1.f;

	FLOAT m_start = 0;
	//���� �ð�
	FLOAT m_delay;
	//��鸲 ��
	INT m_radius;
	//��鸲 ���� ��
	INT m_velocity;
public:
	cCameraManager();
	virtual ~cCameraManager();

	void ResetCamera();
	void Update();
	void SetTransform();

	void ResetSetting();

	void SetShake(float time, int radius, int velocity);
	void Shake();
};

#define CAMERA cCameraManager::GetInst()