#pragma once
#include "cComponent.h"

class cBoxCollider : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:
	RECT m_size;
	vector<OBJ_Tag> m_collistTag;
	vector<string> m_collistName;
	function<void(cObject*)> m_collFunc = [&](cObject* other)->void {};

	virtual void Init() override {}
	virtual void Update() override {}
	virtual void Render() override {}
	virtual void Release() override {}

public:
	cBoxCollider(cObject* obj) : cComponent(obj) {}
	~cBoxCollider() {}

	RECT GetSize()
	{
		return m_size;
	}

	void SetSize(RECT size)
	{
		m_size = size;
	}

	void SetCollFunc(function<void(cObject*)> func)
	{
		m_collFunc = func;
	}

	void AddListTag(OBJ_Tag objTag)
	{
		m_collistTag.push_back(objTag);
	}

	void AddListName(string name)
	{
		m_collistName.push_back(name);
	}
};

