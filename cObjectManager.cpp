#include "DXUT.h"
#include "cObject.h"
#include "cObjectManager.h"

cObjectManager::cObjectManager()
{
}

cObjectManager::~cObjectManager()
{
	for (auto iter : m_objs)
		SAFE_DELETE(iter);
}

void cObjectManager::Render()
{
	
}

void cObjectManager::AddOBJ(cObject* obj, int tagNum)
{
	//오브젝트 매니저 구조

	//플레이어 태그

	//에네미 태그 -> 근접 적, 원거리 적 집단 오브젝트

	//어떻게 오더 순으로 정렬시킬까 적 태그같은 경우 태그안에 또 나뉜다
	//태그마다 오더를 나눌까, 오브젝트별로 오더를 나눌까

	if (m_objs[tagNum] == nullptr) m_objs[tagNum] = obj;
	else DEBUG_LOG("이미 같은 이름의 태그가 있어유...\n");
}

cObject* cObjectManager::FindOBJ(int tagNum)
{
	if (m_objs[tagNum] == nullptr)
		DEBUG_LOG("찾는 태그가 없어유...\n");
	return m_objs[tagNum];
}

