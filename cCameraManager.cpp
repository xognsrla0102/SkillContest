#include "DXUT.h"
#include "cCameraManager.h"

cCameraManager::cCameraManager()
{
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);

	ResetCamera();
}

cCameraManager::~cCameraManager()
{
}

void cCameraManager::ResetCamera()
{
	D3DXMatrixOrthoOffCenterLH(&m_matProj, 0.f, WINSIZEX, WINSIZEY, 0.f, 0.f, 1.f);
	//투영행렬 적용
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void cCameraManager::Update()
{
	D3DXMATRIX matS, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);

	if (m_isShake == TRUE && m_isPause == FALSE)
		Shake();

	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, 0.f);

	m_matView = matS * matT;
}

void cCameraManager::SetTransform()
{
	//뷰 행렬 설정
	DEVICE->SetTransform(D3DTS_VIEW, &m_matView);
}

void cCameraManager::ResetSetting()
{
	if (m_velocity < 0) m_velocity = -m_velocity;
	m_accel = 1;
	m_pos = VEC2(0, 0);
}

void cCameraManager::Shake()
{
	start += D_TIME;
	if (start > m_delay) {
		m_pos.x = rand() % m_accel - rand() % m_accel;
		m_pos.y = rand() % m_accel - rand() % m_accel;
		m_accel += m_velocity;
		start = 0.f;
	}

	if (m_accel > 40) {
		m_accel = 40;
		m_velocity = -m_velocity;
	}
	else if (m_accel < 1) {
		ResetSetting();
		m_isShake = FALSE;
	}
}
