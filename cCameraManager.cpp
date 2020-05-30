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
	D3DXMatrixOrthoLH(&m_matProj, WINSIZEX, -WINSIZEY, 0.f, 1.f);
	//������� ����
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_matProj);
	m_pos = VEC2(WINSIZEX / 2, WINSIZEY / 2);
}

void cCameraManager::Update()
{
	D3DXMATRIX matS, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);

	if (m_isShake == TRUE)
		Shake();

	D3DXMatrixScaling(&matS, m_size, m_size, 1.f);
	D3DXMatrixTranslation(&matT, -m_pos.x, -m_pos.y, 0.f);

	m_matView = matS * matT;
}

void cCameraManager::SetTransform()
{
	//�� ��� ����
	DEVICE->SetTransform(D3DTS_VIEW, &m_matView);
}

void cCameraManager::ResetSetting()
{
	if (m_velocity < 0) m_velocity = -m_velocity;
}

void cCameraManager::SetShake(float time, int radius, int velocity)
{
	//��鸮�� ���߿� ��鸲�� �߻��� ��
	if (m_isShake) {
		//�ð��� �� ���� �� ����
		if (m_delay < time) m_delay = time;
		//��鸲 ���� �������� �� �þ��
		m_radius += radius;
		m_velocity += velocity;
	}
	//�� ��鸮�ٰ� ��鸱 ��
	else {
		m_start = 0;
		m_delay = time;
		m_radius = radius;
		m_velocity = velocity;
		m_isShake = true;
	}
}

void cCameraManager::Shake()
{
	m_start += D_TIME;
	if (m_start < m_delay) {
		m_pos.x += rand() % m_radius - rand() % m_radius;
		m_pos.y += rand() % m_radius - rand() % m_radius;
		m_radius += m_velocity;
	}
	else {
		ResetSetting();
		m_isShake = false;
	}
}
