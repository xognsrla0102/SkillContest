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

void cObjectManager::Update()
{
	for (int i = 0; i < TAG_END; ++i)
		OBJFIND(i)->Update();
}

void cObjectManager::Render()
{
	for (int i = 0; i < TAG_END; ++i)
		OBJFIND(i)->Render();
}

void cObjectManager::AddOBJ(cObject* obj, int tagNum)
{
	//오브젝트 매니저 구조

	//플레이어 태그

	//에네미 태그 -> 근접 적, 원거리 적 집단 오브젝트
	//태그마다 오더를 나눔
	//에네미 태그에서 렌더를 하면 에네미 매니저 속에 들어가고
	//그 속의 렌더함수를 호출함
	//에네미 매니저의 렌더에선 모든 적기들의 렌더링을 하도록 처리

	if (m_objs[tagNum] == nullptr) m_objs[tagNum] = obj;
	else DEBUG_LOG("이미 같은 이름의 태그가 있어유...\n");
}

cObject* cObjectManager::FindOBJ(int tagNum)
{
	if (m_objs[tagNum] == nullptr)
		DEBUG_LOG("찾는 태그가 없어유...\n");
	return m_objs[tagNum];
}

