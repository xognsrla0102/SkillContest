#include "DXUT.h"
#include "cImageManager.h"

cImageManager::cImageManager()
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

cImageManager::~cImageManager()
{
	for (auto iter : m_textures) {
		iter.second->texturePtr->Release();
		SAFE_DELETE(iter.second);
	}
	m_textures.clear();

	m_sprite->Release();
	SAFE_RELEASE(m_font);
}

void cImageManager::AddTexture(const string& key, const string& path)
{
	if (m_textures.find(key) != m_textures.end()) {
		DEBUG_LOG("%s 텍스쳐가 이미 있습니다.\n", key.c_str());
		return;
	}
	LPDIRECT3DTEXTURE9 texturePtr;
	D3DXIMAGE_INFO info;
	if (D3DXCreateTextureFromFileExA(
		DEVICE, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &texturePtr) == S_OK) {
		cTexture* text = new cTexture(texturePtr, info);
		m_textures[key] = text;
	}
}

cTexture* cImageManager::FindTexture(const string& key)
{
	auto find = m_textures.find(key);
	if (find == m_textures.end()) {
		DEBUG_LOG("%s 텍스쳐가 없습니다.\n", key.c_str());
		return nullptr;
	}
	return find->second;
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
	D3DXMATRIXA16 mat, s, r, t;
	D3DXMatrixIdentity(&mat);

	D3DXMatrixScaling(&s, size.x, size.y, 1.f);
	D3DXMatrixRotationZ(&r, D3DXToRadian(rot));
	D3DXMatrixTranslation(&t, pos.x, pos.y, 0.f);

	mat = s * r * t;

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
	D3DXMATRIXA16 mat, s, r, t;
	D3DXMatrixIdentity(&mat);

	D3DXMatrixScaling(&s, size.x, size.y, 1.f);
	D3DXMatrixRotationZ(&r, D3DXToRadian(rot));
	D3DXMatrixTranslation(&t, pos.x, pos.y, 0.f);

	mat = s * r * t;

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

vector<cTexture*> cImageManager::FindAnimation(const string& key)
{
	char _key[256];
	cTexture* image;
	vector<cTexture*> result;
	for (int i = 0;; ++i) {
		sprintf(_key, "%s%d", key.c_str(), i);
		image = FindTexture(_key);
		if (image) result.push_back(image);
		else break;
	}
	return result;
}

