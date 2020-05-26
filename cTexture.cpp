#include "DXUT.h"
#include "cTexture.h"

cTexture::cTexture(const char* sz)
{
	D3DXCreateTextureFromFileExA(
		DEVICE, sz, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
		NULL, &m_info, nullptr, &m_text
	);
}

cTexture::~cTexture()
{
	SAFE_RELEASE(m_text);
}