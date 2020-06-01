#pragma once
#include "cSingleton.hpp"

class cCameraManager : public cSingleton<cCameraManager>
{
private:
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
	FLOAT m_start = 0;
	BOOL m_isShake = FALSE;
	VEC2 m_pos = VEC2(0, 0);
	FLOAT m_size = 1.f;
public:
	//Áøµ¿ ½Ã°£
	FLOAT m_delay;
	//Èçµé¸² Æø
	INT m_radius;
	//Èçµé¸² Áõ°¡ Æø
	INT m_velocity;
public:
	__declspec(property(get = GetSize, put = SetSize)) float p_size;
	__declspec(property(get = GetPos, put = SetPos)) VEC2 p_pos;
public:
	cCameraManager();
	virtual ~cCameraManager();

	void ResetCamera();
	void Update();
	void SetTransform();

	void ResetSetting();

	VEC2& GetPos() { return m_pos; }
	float& GetSize() { return m_size; }

	void SetPos(VEC2 pos);
	void SetSize(float size);

	void SetShake(float time, int radius, int velocity);
	void Shake();
};

#define CAMERA cCameraManager::GetInst()