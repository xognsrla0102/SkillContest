#pragma once
#include "cSingleton.hpp"

class cObjectManager : public cSingleton<cObjectManager>
{
private:
	friend class cComponent;
private:
	list<cObject*> m_objs;
	list<cObject*> m_collObjs;

	cObject* m_player;
	cObject* m_boss;

	void CheckBoxCollision(cObject* obj);
	void CheckCircleCollision(cObject* obj);
public:
	cObjectManager();
	virtual ~cObjectManager();

	void Init();
	void Update();
	void Render();
	void Release();

	void ClearAll();

	cObject* Create(string name, VEC2 pos, INT depth, OBJ_Tag objTag);

	list<cObject*> Find(string name);
	list<cObject*> Find(OBJ_Tag objTag);

	void With(string name, function<void(cObject*)> func);
	void With(OBJ_Tag objTag, function<void(cObject*)> func);
	void With(cObject* obj, function<void(cObject*)> func);

	cObject* GetPlayer()
	{
		return m_player;
	}

	cObject* GetBoss()
	{
		return m_boss;
	}

	void SetPlayer(cObject* player)
	{
		m_player = player;
	}

	void SetBoss(cObject* boss)
	{
		m_boss = boss;
	}
};

#define OBJECT cObjectManager::GetInst()