#pragma once

//����.. ���ʿ� �������� ��ġ�� ���� �ʿ䰡 ����. �ܼ� �̹�����
//���� ������ ������ �Ǳ� ����
//��ġ, ���� ������ �̹����� ��� ���� ��ü���� �ñ⵵�� ����.
class cImage
{
public:
	cTexture* m_img = nullptr;

	float m_a = 255.f;
	float m_r = 255.f;
	float m_g = 255.f;
	float m_b = 255.f;

	D3DXCOLOR m_color = D3DCOLOR_ARGB(255, 255, 255, 255);

	cImage() {}
	~cImage() {}

	void SetNowRGB() { m_color = D3DCOLOR_ARGB((int)m_a, (int)m_r, (int)m_g, (int)m_b); }
};

