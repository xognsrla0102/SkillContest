#include "DXUT.h"
#include "cObject.h"

void cObject::Release()
{
	for (auto iter : m_components) {
		iter->Release();
		SAFE_DELETE(iter);
	}
	m_components.clear();
}

