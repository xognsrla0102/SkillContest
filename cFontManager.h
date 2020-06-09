#pragma once
#include "cSingleton.hpp"

class cTimer;
class cFontInfo {
private:
	cTimer* m_timer = nullptr;
	string m_text;
	VEC2 m_pos;
	D3DCOLOR m_color = D3DCOLOR_ARGB(255, 255, 255, 255);
	BOOL m_isScoreText = FALSE;
	int m_size = 20;
public:
	BOOL m_isDone = FALSE;
public:
	cFontInfo(string text, VEC2 pos, INT printTime, BOOL isScoreText = FALSE, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255), int size = 20);
	~cFontInfo();

	void Update();
	void Render();
};

class cFontManager : public cSingleton<cFontManager>
{
private:
	vector<cFontInfo*> m_fonts;
public:
	cFontManager() {}
	virtual ~cFontManager();

	void Update();
	void Render();
	void Release();

	void AddFont(string text, VEC2 pos, INT printTime, BOOL isScoreText = FALSE, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255), int size = 20);
};

#define FONT cFontManager::GetInst()