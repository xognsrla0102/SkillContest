#pragma once
#include "cScene.h"

template <typename T1, typename T2>
struct sData {
public:
	T1 m_idx1;
	T2 m_idx2;
	int m_cnt;
public:
	sData(T1 idx1, T2 idx2, int cnt = 1)
		: m_idx1(idx1), m_idx2(idx2), m_cnt(cnt)
	{}
};

class cLoadScene : public cScene
{
private:
	cImage* m_bg = nullptr;

	vector<sData<string, wstring>*> m_sounds;
	vector<sData<string, string>*>  m_imgs;

	int m_nowLoad[2] = { 0 };

public:
	cLoadScene();
	virtual ~cLoadScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void Load(const string& key, const wstring& path) {
		m_sounds.push_back(new sData<string, wstring>(key, path));
	}

	void Load(const string& key, const string& path, int cnt = 1) {
		if (cnt < 2)
			m_imgs.push_back(new sData<string, string>(key, path));
		else
			m_imgs.push_back(new sData<string, string>(key, path, cnt));
	}
};

