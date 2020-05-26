#include "DXUT.h"
#include "cMultiTexture.h"

cMultiTexture::cMultiTexture()
{
}

cMultiTexture::~cMultiTexture()
{
	for (auto iter : m_multiImgs)
		SAFE_DELETE(iter);
	m_multiImgs.clear();
}

void cMultiTexture::AddImage(string path, int cnt)
{
	char sz[128];
	for (int i = 0; i < cnt; i++) {
		sprintf(sz, path.c_str(), i);
		m_multiImgs.push_back(new cTexture(sz));
	}
}

cTexture* cMultiTexture::FindImage(int cnt)
{
	if (cnt < 0) {
		DEBUG_LOG("인덱스가 0미만이에유...\n");
		return nullptr;
	}
	return m_multiImgs[cnt];
}
