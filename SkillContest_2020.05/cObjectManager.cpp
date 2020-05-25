#include "DXUT.h"
#include "cObjectManager.h"

cObjectManager::cObjectManager()
{
	Init();
}

cObjectManager::~cObjectManager()
{
	Release();
}

void cObjectManager::CheckBoxCollision(cObject* obj)
{
	cBoxCollider* boxColl = obj->GetComponent<cBoxCollider>();
	if ((boxColl->m_collistTag.size() == 0 && boxColl->m_collistName.size() == 0)
		|| boxColl->GetEnable() == FALSE) return;

	list<cObject*> others;

	for (auto iter : m_objs) {
		if (iter == obj) continue;
		for (int i = 0; i < boxColl->m_collistTag.size(); ++i) {
			if (iter->GetTag() == boxColl->m_collistTag[i]) {
				others.push_back(iter);
				goto Next;
			}
		}
		for (int i = 0; i < boxColl->m_collistName.size(); ++i) {
			if (iter->GetName() == boxColl->m_collistName[i]) {
				others.push_back(iter);
				break;
			}
		}
	Next:
		1;
	}

	for (auto iter : others) {
		if (iter->GetComponent<cBoxCollider>()) {
			if (Math::CheckCollBoxBox(
				boxColl->GetSize(),
				iter->GetComponent<cBoxCollider>()->GetSize()
			)) {
				boxColl->m_collFunc(iter);
				iter->GetComponent<cBoxCollider>()->m_collFunc(obj);
			}
		}
		else {
			if (Math::CheckCollBoxCir(
				obj->GetPos(), boxColl->GetSize(), iter->GetPos(),
				iter->GetComponent<cCircleCollider>()->GetRad()
			)) {
				boxColl->m_collFunc(iter);
				iter->GetComponent<cCircleCollider>()->m_collFunc(obj);
			}
		}
	}
}

void cObjectManager::CheckCircleCollision(cObject* obj)
{
	cCircleCollider* cirColl = obj->GetComponent<cCircleCollider>();
	if ((cirColl->m_collistTag.size() == 0 && cirColl->m_collistName.size() == 0)
		|| cirColl->GetEnable() == FALSE) return;

	cCircleCollider* otherColl;

	VEC2 pos = obj->m_pos;

	INT rad = cirColl->m_rad;
	INT tagSize = cirColl->m_collistTag.size();
	INT nameSize = cirColl->m_collistName.size();
	INT i = 0;

	FLOAT x, y, dir, dist = 0;

	for (auto iter : m_objs) {
		x = pos.x - iter->m_pos.x;
		y = pos.y - iter->m_pos.y;
		dir = atan2(y, x);
		dist = abs(x * cos(dir)) + abs(y * sin(dir));
		if (dist <= 35) {
			otherColl = iter->GetComponent<cCircleCollider>();
			for (i = 0; i < nameSize; ++i) {
				if (iter->m_name == cirColl->m_collistName[i]) {
					if (dist <= rad + otherColl->m_rad) {
						cirColl->m_collFunc(iter);
						otherColl->m_collFunc(obj);
					}
					goto next;
				}
			}
			for (i = 0; i < tagSize; ++i) {
				if (iter->m_tag == cirColl->m_collistTag[i]) {
					if (dist <= rad + otherColl->m_rad) {
						cirColl->m_collFunc(iter);
						otherColl->m_collFunc(obj);
					}
					break;
				}
			}
		}
	next:
		1;
	}
}

void cObjectManager::Init()
{
	m_boss = nullptr;
}

void cObjectManager::Update()
{
	for (auto& iter = m_objs.begin(); iter != m_objs.end();)
	{
		if ((*iter)->GetEnable() == FALSE)
		{
			iter++;
			continue;
		}
		for (auto iter : (*iter)->m_components)
		{
			if (iter->GetEnable())
				iter->Update();
		}

		if ((*iter)->GetComponent<cCircleCollider>())
			CheckCircleCollision((*iter));

		if ((*iter)->m_destroy == TRUE)
		{
			(*iter)->Release();
			SAFE_DELETE((*iter));
			iter = m_objs.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void cObjectManager::Render()
{
	list<cObject*> RenderList = m_objs;
	//depth 가 큰 순으로 먼저 렌더.. 즉 depth 가 낮을 수록 위에 그려짐
	RenderList.sort([&](cObject* pPrev, cObject* pNext)->BOOL { return pPrev->m_depth > pNext->m_depth; });
	for (auto& iter = RenderList.begin(); iter != RenderList.end();)
	{
		(*iter)->Render();
		for (auto iter : (*iter)->m_components)
		{
			if (iter->GetEnable())
				iter->Render();
		}
		iter++;
	}
}

void cObjectManager::Release()
{
	for (auto iter : m_objs) {
		iter->Release();
		SAFE_DELETE(iter);
	}
	m_objs.clear();
}

void cObjectManager::ClearAll()
{
	for (auto iter : m_objs)
		iter->Destroy();

	OBJECT->SetBoss(nullptr);
	OBJECT->SetPlayer(nullptr);
}

cObject* cObjectManager::Create(string name, VEC2 pos, INT depth, OBJ_Tag objTag)
{
	cObject* Obj = new cObject;
	Obj->m_name = name;
	Obj->m_pos = pos;
	Obj->m_depth = depth;
	Obj->m_tag = objTag;
	Obj->Init();
	m_objs.push_back(Obj);
	return Obj;
}

list<cObject*> cObjectManager::Find(string name)
{
	list<cObject*> result;
	for (auto iter : m_objs)
		if (iter->m_name == name)
			result.push_back(iter);
	return result;
}

list<cObject*> cObjectManager::Find(OBJ_Tag objTag)
{
	list<cObject*> result;
	for (auto iter : m_objs)
		if (iter->m_tag == objTag)
			result.push_back(iter);
	return result;
}

void cObjectManager::With(string name, function<void(cObject*)> func)
{
	list<cObject*> objs = Find(name);
	for (auto iter : objs)
		func(iter);
}

void cObjectManager::With(OBJ_Tag objTag, function<void(cObject*)> func)
{
	list<cObject*> objs = Find(objTag);
	for (auto iter : objs)
		func(iter);
}

void cObjectManager::With(cObject* obj, function<void(cObject*)> func)
{
	func(obj);
}
