#include "DXUT.h"
#include "cCameraManager.h"

cCameraManager::cCameraManager()
{
	//LookAt 함수로 카메라의 기본 위치와 바라보는 방향을 정할 필요가 없음
	//2D니까.. 그냥 기본상태(정면)보면 됨.
	//항등항렬로 설정해두고 확대축소, 이동처리만 해서 뷰행렬에 전달하면 됨

	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);

	//직교 투영
	D3DXMatrixOrthoOffCenterLH(&m_matProj, 0.f, winSizeX, winSizeY, 0.f, 0.f, 1.f);

	//투영행렬 적용
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

cCameraManager::~cCameraManager()
{
}

void cCameraManager::ResetCamera()
{
	D3DXMatrixOrthoOffCenterLH(&m_matProj, 0.f, winSizeX, winSizeY, 0.f, 0.f, 1.f);
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
	if (timeGetTime() - start > m_delay) {
		m_pos.x = rand() % m_accel - rand() % m_accel;
		m_pos.y = rand() % m_accel - rand() % m_accel;
		m_accel += m_velocity;
		start = timeGetTime();
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
