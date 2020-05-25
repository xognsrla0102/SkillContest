#pragma once
#include "cComponent.h"

class cCircleCollider : public cComponent
{
private:
	friend class cObject;
	friend class cObjectManager;
private:
	INT m_rad = 0;
	vector<OBJ_Tag> m_collistTag;
	vector<string> m_collistName;
	function<void(cObject*)> m_collFunc = [&](cObject* other)->void {};

	virtual void Init() override {};
	virtual void Update() override {};
	virtual void Render() override {};
	virtual void Release() override {};
public:
	cCircleCollider(cObject* obj) : cComponent(obj) {}
	virtual ~cCircleCollider() {}

	INT GetRad() {
		return m_rad;
	}

	void SetRad(INT rad) {
		m_rad = rad;
	}

	void SetCollFunc(function<void(cObject*)> func) {
		m_collFunc = func;
	}

	void AddListTag(OBJ_Tag objTag) {
		m_collistTag.push_back(objTag);
	}

	void AddListName(string name) {
		m_collistName.push_back(name);
	}
};

