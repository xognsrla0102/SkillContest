#include "DXUT.h"
#include "cRenderer.h"

cRenderer::cRenderer(cObject* Object) :cComponent(Object)
{
}

cRenderer::~cRenderer()
{
}

void cRenderer::Init()
{
	m_alpha = 255;
}

void cRenderer::Update()
{

}

void cRenderer::Render()
{
	IMAGE->Render(m_image, 
		m_pObj->GetPos(), 
		m_pObj->GetScale(), 
		m_pObj->GetRot(),
		D3DCOLOR_ARGB(m_alpha, 255, 255, 255)
	);
}

void cRenderer::Release()
{

}
