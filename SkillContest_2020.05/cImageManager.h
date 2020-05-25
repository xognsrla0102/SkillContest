#pragma once
#include "cSingleton.hpp"

struct cTexture
{
public:
	LPDIRECT3DTEXTURE9 texturePtr;
	D3DXIMAGE_INFO info;

	FLOAT m_a = 255.f;
	FLOAT m_r = 255.f;
	FLOAT m_g = 255.f;
	FLOAT m_b = 255.f;

	D3DXCOLOR m_color = D3DCOLOR_ARGB((INT)m_a, (INT)m_r, (INT)m_g, (INT)m_b);
public:
	cTexture(LPDIRECT3DTEXTURE9 texturePtr, D3DXIMAGE_INFO info)
		:texturePtr(texturePtr), info(info) {}
	__inline VOID SetNowRGB() { m_color = D3DCOLOR_ARGB((INT)m_a, (INT)m_r, (INT)m_g, (INT)m_b); }
};

class cImageManager : public cSingleton<cImageManager>
{
private:
	LPD3DXSPRITE m_sprite = nullptr;
	map<string, cTexture*> m_textures;
	LPD3DXFONT m_font;
public:
	cImageManager();
	virtual ~cImageManager();

	void AddTexture(const string& key, const string& path);
	cTexture* FindTexture(const string& key);

	void Begin(BOOL isUI);
	void ReBegin(BOOL isUI);
	void End();

	void Render(cTexture* texturePtr, VEC2 pos, VEC2 size, FLOAT rot = 0.f, BOOL isCenterRot = FALSE, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	void CenterRender(cTexture* texturePtr, VEC2 pos, VEC2 size, FLOAT rot = 0.f, BOOL isCenterRot = FALSE, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));

	void DrawFont(string text, VEC2 pos, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));

	void LostDevice();
	void ResetDevice();

	vector<cTexture*> FindAnimation(const string& key);
};

#define IMAGE cImageManager::GetInst()