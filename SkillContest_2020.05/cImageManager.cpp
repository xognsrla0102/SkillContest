#include "DXUT.h"
#include "cImageManager.h"

void cTexture::Render(VEC2 pos, VEC2 size, FLOAT rot, D3DXCOLOR color)
{
	IMAGE->Render(this, pos, size, rot, color);
}

void cTexture::Render(FLOAT x, FLOAT y, FLOAT rot)
{
	IMAGE->Render(this, x, y, rot);
}

void cTexture::CenterRender(VEC2 pos, VEC2 size, FLOAT rot, D3DXCOLOR color)
{
	IMAGE->CenterRender(this, pos, size, rot, color);
}

void cTexture::CenterRender(FLOAT x, FLOAT y, FLOAT rot)
{
	IMAGE->CenterRender(this, x, y, rot);
}

void cImageManager::Init()
{
	D3DXCreateSprite(DEVICE, &m_sprite);
}

void cImageManager::Release()
{
	for (auto iter : m_images) {
		iter.second->texturePtr->Release();
		SAFE_DELETE(iter.second);
	}
	m_images.clear();
	m_sprite->Release();
}

cImageManager::cImageManager() : m_sprite(nullptr)
{
	Init();
}

cImageManager::~cImageManager()
{
	Release();
}

void cImageManager::AddImage(const string& key, const string& path)
{
	if (m_images.find(key) != m_images.end()) {
		DEBUG_LOG("같은 이름의 이미지가 있습니다.\n");
		return;
	}

	LPDIRECT3DTEXTURE9 texturePtr;
	D3DXIMAGE_INFO info;
	if (D3DXCreateTextureFromFileExA(
		DEVICE, key.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &texturePtr) == S_OK) {
		cTexture* text = new cTexture(texturePtr, info);
		m_images[key] = text;
	}
}

cTexture* cImageManager::FindImage(const string& key)
{
	if (m_images.find(key) == m_images.end()) {
		DEBUG_LOG("찾는 이미지가 없습니다.\n");
		return nullptr;
	}
	return m_images.find(key)->second;
}

void cImageManager::Begin()
{
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void cImageManager::End()
{
	m_sprite->End();
}

void cImageManager::Render(cTexture* texturePtr, VEC2 pos, VEC2 size, FLOAT rot, BOOL isCenterRot, D3DXCOLOR color)
{
	if (!texturePtr) {
		DEBUG_LOG("텍스쳐 포인터가 없습니다.\n");
		return;
	}
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	m_sprite->SetTransform(&mat);

	if (isCenterRot) {
		m_sprite->Draw(
			texturePtr->texturePtr, nullptr,
			&VEC3(texturePtr->info.Width / 2.f, texturePtr->info.Height / 2.f, 0.f),
			nullptr, color
		);
	}
	else {
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, color);
	}
}

void cImageManager::CenterRender(cTexture* texturePtr, VEC2 pos, VEC2 size, FLOAT rot, BOOL isCenterRot, D3DXCOLOR color)
{
	if (!texturePtr) {
		DEBUG_LOG("텍스쳐 포인터가 없습니다.\n");
		return;
	}
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	m_sprite->SetTransform(&mat);

	if (isCenterRot) {
		m_sprite->Draw(
			texturePtr->texturePtr, nullptr,
			&VEC3(texturePtr->info.Width / 2.f, texturePtr->info.Height / 2.f, 0.f),
			nullptr, color
		);
	}
	else {
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, color);
	}
}

void cImageManager::RenderText(string Text, VEC2 Pos, VEC2 Size, D3DXCOLOR Color)
{
}

void cImageManager::RenderTextCenter(string Text, VEC2 Pos, VEC2 Size, D3DXCOLOR Color)
{
}

void cImageManager::LostDevice()
{
	m_sprite->OnLostDevice();
}

void cImageManager::ResetDevice()
{
	m_sprite->OnResetDevice();
}

vector<cTexture*> cImageManager::makeVector(const string& key)
{
	return vector<cTexture*>();
}

