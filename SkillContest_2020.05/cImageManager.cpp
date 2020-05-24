#include "DXUT.h"
#include "cImageManager.h"

void cTexture::Render(VEC2 pos, VEC2 size, FLOAT rot, BOOL isCenterRot, D3DXCOLOR color)
{
	IMAGE->Render(this, pos, size, rot, isCenterRot, color);
}

void cTexture::CenterRender(VEC2 pos, VEC2 size, FLOAT rot, BOOL isCenterRot, D3DXCOLOR color)
{
	IMAGE->CenterRender(this, pos, size, rot, isCenterRot, color);
}

void cImageManager::Init()
{
	D3DXCreateSprite(DEVICE, &m_sprite);

	D3DXCreateFontW(
		DEVICE,
		20,
		0,
		FW_NORMAL,
		1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"Arial",
		&m_font
	);
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
		DEBUG_LOG("%s 이미지가 이미 있습니다.\n", key.c_str());
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
		DEBUG_LOG("%s 이미지가 없습니다.\n", key.c_str());
		return nullptr;
	}
	return m_images.find(key)->second;
}

void cImageManager::Begin(BOOL isUI)
{
	if (isUI)
		m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
	else
		m_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
}

void cImageManager::ReBegin(BOOL isUI)
{
	End();
	Begin(isUI);
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

void cImageManager::DrawFont(string text, VEC2 pos, D3DCOLOR color)
{
	RECT rt = { pos.x, pos.y, 0, 0 };

	m_font->DrawTextW(
		nullptr,
		(LPWSTR)text.c_str(),
		-1,
		&rt,
		DT_NOCLIP,
		color
	);
}

void cImageManager::LostDevice()
{
	m_sprite->OnLostDevice();
}

void cImageManager::ResetDevice()
{
	m_sprite->OnResetDevice();
}

vector<cTexture*> cImageManager::MakeAnimation(const string& key)
{
	char _key[50];
	cTexture* image;
	sprintf(_key, "%s0", key.c_str());
	image = FindImage(_key);
	vector<cTexture*> result;
	result.push_back(image);
	for (int i = 1;; ++i) {
		sprintf(_key, "%s%d", key.c_str(), i);
		if (image = FindImage(_key))
			result.push_back(image);
		else
			break;
	}
	return result;
}

