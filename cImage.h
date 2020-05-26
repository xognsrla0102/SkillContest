#pragma once

//수정.. 애초에 개별적인 위치를 가질 필요가 없다. 단순 이미지는
//색상 정보만 잇으면 되기 때문
//위치, 각도 정보는 이미지를 담는 하위 객체에게 맡기도록 하자.
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

