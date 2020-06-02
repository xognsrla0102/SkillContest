#pragma once
#include "cImage.h"

class cButton : public cImage
{
public:
	string m_key;
	string m_path;

	bool m_isOn = false;
	
	VEC2 m_pos;

	VEC2 m_size;
	VEC2 m_oldSize;
	VEC2 m_deltaSize;

	float m_rot;
public:
	cButton(VEC2 pos, VEC2 deltaSize, VEC2 size = VEC2(1, 1));
	~cButton() {}

	void Update();
	void Render();

	void SetImage(string key);
};

