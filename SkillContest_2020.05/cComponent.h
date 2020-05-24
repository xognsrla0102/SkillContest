#pragma once

class cObject;
class cComponent
{
protected:
	cObject* m_pObj;
private:
	friend class cObject;
	friend class cObjectManager;
	BOOL m_enable;
private:
	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
public:
	__declspec(property(get = GetEnable, put = setEnable)) BOOL d_enable;
public:
	cComponent(cObject* obj) : m_pObj(obj) {}
	virtual ~cComponent() {}

	void SetEnable(BOOL enable) {
		m_enable = enable;
	}

	BOOL GetEnable() {
		return m_enable;
	}
};

