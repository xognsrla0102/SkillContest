#pragma once

class cObject abstract
{
protected:
	//窜老老 版快
	cImage* m_img = nullptr;

	//局聪皋捞记 老 版快
	cAnimation* m_ani = nullptr;

	VEC2 m_pos = VEC2(0, 0);
	VEC2 m_size = VEC2(1, 1);

	FLOAT m_rot = 0.f;

	BOOL m_isLive = TRUE;

	BOOL m_isActive = FALSE;

	string m_objName;
public:
	cObject() {}
	virtual ~cObject() {}

	virtual void Update() PURE;
	virtual void Render() PURE;

	bool OutMapChk(int offset);

	cTexture* GetImg() { return m_img->m_text; }
	VEC2 GetPos() { return m_pos; }
	VEC2 GetSize() { return m_size; }
	FLOAT GetRot() { return m_rot; }
	BOOL GetLive() { return m_isLive; }
	BOOL GetActive() { return m_isActive; }
	cAnimation* GetAni() { return m_ani; }
	RECT GetObjCollider();
	string GetName() { return m_objName; }

	VEC2& GetRefPos() { return m_pos; }
	VEC2& GetRefSize() { return m_size; }
	BOOL& GetRefLive() { return m_isLive; }

	void SetImg(cTexture* img) { m_img->m_text = img; }
	void SetPos(VEC2 pos) { m_pos = pos; }
	void SetSize(VEC2 size) { m_size = size; }
	void SetRot(FLOAT rot) { m_rot = rot; }
	void SetLive(BOOL isLive) { m_isLive = isLive; }
	void SetActive(BOOL isActive) { m_isActive = isActive; }
	void SetName(string name) { m_objName = name; }
};

