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
	p_pos = VEC2(WINSIZEX / 2, WINSIZEY / 2);
}

void cCameraManager::Update()
{
	if		(KEYPRESS('A'))	SetSize(m_size * 1.01);
	else if (KEYPRESS('D'))	SetSize(m_size / 1.01);

	D3DXMATRIX matS, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	if (m_isShake == TRUE) Shake();
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
	p_pos = VEC2(WINSIZEX / 2 + 300 * p_size, WINSIZEY / 2);
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

void cCameraManager::SetPos(VEC2 pos)
{
	m_pos = (pos *= m_size);
}

void cCameraManager::SetSize(float size)
{
	m_pos *= (size / m_size);
	m_size = size;
}

void cCameraManager::Shake()
{
	m_start += D_TIME;
	if (m_start < m_delay) {
		p_pos.x += rand() % m_radius - rand() % m_radius;
		p_pos.y += rand() % m_radius - rand() % m_radius;
		m_radius += m_velocity;
	}
	else {
		ResetSetting();
		m_isShake = false;
	}
}
