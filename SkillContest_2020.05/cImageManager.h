#pragma once
#include "cSingleton.hpp"

struct cTexture
{
	LPDIRECT3DTEXTURE9 texturePtr;
	D3DXIMAGE_INFO info;

	cTexture(LPDIRECT3DTEXTURE9 texturePtr, D3DXIMAGE_INFO info)
		:texturePtr(texturePtr), info(info)
	{
	}

	void Render(VEC2 pos, VEC2 size, FLOAT rot = 0.f, BOOL isCenterRot = FALSE, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	void CenterRender(VEC2 pos, VEC2 size, FLOAT rot = 0.f, BOOL isCenterRot = FALSE, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
};

class cImageManager : public cSingleton<cImageManager>
{
private:
	LPD3DXSPRITE m_sprite;
	map<string, cTexture*> m_images;
	LPD3DXFONT m_font;
private:
	void Init();
	void Release();
public:
	cImageManager();
	virtual ~cImageManager();

	void AddImage(const string& key, const string& path);
	cTexture* FindImage(const string& key);

	void Begin(BOOL isUI);
	void ReBegin(BOOL isUI);
	void End();

	void Render(cTexture* texturePtr, VEC2 pos, VEC2 size, FLOAT rot = 0.f, BOOL isCenterRot = FALSE, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	void CenterRender(cTexture* texturePtr, VEC2 pos, VEC2 size, FLOAT rot = 0.f, BOOL isCenterRot = FALSE, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));

	void DrawFont(string text, VEC2 pos, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));

	void LostDevice();
	void ResetDevice();

	vector<cTexture*> MakeAnimation(const string& key);
};

#define IMAGE cImageManager::GetInst()