#pragma once

class cTexture
{
public:
	LPDIRECT3DTEXTURE9 m_text = nullptr;
	D3DXIMAGE_INFO m_info;

	cTexture() {}
	cTexture(const char* sz);
	virtual ~cTexture();
};
