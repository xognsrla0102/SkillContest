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

	void Render(VEC2 pos, VEC2 size, FLOAT rot = 0.f, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	void Render(FLOAT x, FLOAT y, FLOAT rot = 0.f);

	void CenterRender(VEC2 pos, VEC2 size, FLOAT rot = 0.f, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	void CenterRender(FLOAT x, FLOAT y, FLOAT rot = 0.f);
};

class cImageManager : public cSingleton<cImageManager>
{
private:
	LPD3DXSPRITE m_sprite;
	map<string, cTexture*> m_images;
private:
	void Init();
	void Release();
public:
	cImageManager();
	~cImageManager();

	void AddImage(const string& key, const string& path);
	cTexture* FindImage(const string& key);

	void Begin();
	void End();

	void Render(cTexture* texturePtr, VEC2 pos, VEC2 size, FLOAT rot = 0.f, BOOL isCenterRot = FALSE, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	void CenterRender(cTexture* texturePtr, VEC2 pos, VEC2 size, FLOAT rot = 0.f, BOOL isCenterRot = FALSE, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));

	void RenderText(string Text, VEC2 Pos, VEC2 Size, D3DXCOLOR Color = D3DCOLOR_ARGB(255, 255, 255, 255));
	void RenderTextCenter(string Text, VEC2 Pos, VEC2 Size, D3DXCOLOR Color = D3DCOLOR_ARGB(255, 255, 255, 255));

	void LostDevice();
	void ResetDevice();

	vector<cTexture*> makeVector(const string& key);
};

#define IMAGE cImageManager::GetInst()