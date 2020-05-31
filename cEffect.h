#pragma once

class cEffect
{
public:
	cAnimation* m_ani;
	string m_imgName;

	VEC2 m_pos;
	VEC2 m_velSize;
	VEC2 m_size;

	VEC2 m_dir;

	FLOAT m_a = 255.f;
	FLOAT m_r = 255.f;
	FLOAT m_g = 255.f;
	FLOAT m_b = 255.f;

	FLOAT m_alphaSpeed;

	FLOAT m_delay;

	INT m_imgCnt;

	BOOL m_isDone = FALSE;

	D3DCOLOR m_color;

public:
	cEffect(const string name, int imgCnt, float delay, VEC2 pos, VEC2 dir, VEC2 velSize = VEC2(0, 0), VEC2 size = VEC2(1, 1), FLOAT alphaSpeed = 0.f, VEC4 argb = VEC4(255, 255, 255, 255));
	~cEffect();

	void Update();
	void Render();

	void SetColor() { m_color = D3DCOLOR_ARGB((INT)m_a, (INT)m_r, (INT)m_g, (INT)m_b); }
};

