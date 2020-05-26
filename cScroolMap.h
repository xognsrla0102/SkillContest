#pragma once
class cScroolMap
{
private:
	cImage* m_img1, *m_img2;
	VEC2 pos1, pos2;
	int m_downSpd;
public:
	__declspec(property(get = GetSpd, put = SetSpd)) int p_downSpd;
public:
	cScroolMap(cTexture* text);
	~cScroolMap();

	void Init();
	void Update();
	void Render();
	void Release();

	int GetSpd() { return m_downSpd; }
	void SetSpd(int downSpd) { m_downSpd = downSpd; }
};

