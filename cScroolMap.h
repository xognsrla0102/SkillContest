#pragma once
class cScroolMap
{
private:
	cImage* m_img1, *m_img2;
	vector<cImage*> m_gas;
	VEC2 pos1, pos2;
	cTimer* m_createGas;
public:
	float m_mapSpd;
	float m_gasSpd;
public:
	cScroolMap(cTexture* text);
	~cScroolMap();

	void Init();
	void Update();
	void Render();
	void Release(); 
};

