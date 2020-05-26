#pragma once
#include "cSingleton.hpp"

class cMultiTexture;
class cImageManager : public cSingleton<cImageManager>
{
private:
	friend class cSingleton<cImageManager>;
private:
	map<string, cMultiTexture*> m_imgs;
	LPD3DXSPRITE m_sprite;
	LPD3DXFONT m_font;
public:
	cImageManager();
	virtual ~cImageManager();

	void Begin(bool isUI);
	void End();
	void ReBegin(bool isUI);

	void LostDevice();
	void ResetDevice();

	void AddTexture(string name, string path, int cnt = 1);
	cTexture* FindTexture(string name, int cnt = 0);

	void Render(cTexture* text, VEC2 pos, VEC2 size = VEC2(1.f, 1.f), float rot = 0, bool isCenterRot = false, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	void CenterRender(cTexture* text, VEC2 pos, VEC2 center, float size = 1, float rot = 0, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));

	void DrawFont(string text, VEC2 pos, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
};

#define IMAGE cImageManager::GetInst()
#define DRAW_NUM(i, j) IMAGE->DrawNum(i, j)
#define DRAW_NUM_SIZE(i, j, k) IMAGE->DrawNum(i, j, k)
#define DRAW_FRAME(i, j) IMAGE->DrawFrame(i, j)