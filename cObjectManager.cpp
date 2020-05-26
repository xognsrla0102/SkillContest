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
	//������Ʈ �Ŵ��� ����

	//�÷��̾� �±�

	//���׹� �±� -> ���� ��, ���Ÿ� �� ���� ������Ʈ
	//�±׸��� ������ ����
	//���׹� �±׿��� ������ �ϸ� ���׹� �Ŵ��� �ӿ� ����
	//�� ���� �����Լ��� ȣ����
	//���׹� �Ŵ����� �������� ��� ������� �������� �ϵ��� ó��

	if (m_objs[tagNum] == nullptr) m_objs[tagNum] = obj;
	else DEBUG_LOG("�̹� ���� �̸��� �±װ� �־���...\n");
}

cObject* cObjectManager::FindOBJ(int tagNum)
{
	if (m_objs[tagNum] == nullptr)
		DEBUG_LOG("ã�� �±װ� ������...\n");
	return m_objs[tagNum];
}

