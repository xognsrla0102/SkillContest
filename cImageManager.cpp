#include "DXUT.h"
#include "cMultiTexture.h"
#include "cImageManager.h"

cImageManager::cImageManager()
{
	D3DXCreateSprite(DEVICE, &m_sprite);

	D3DXCreateFontA(
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
		"Arial",
		&m_font
	);
}

cImageManager::~cImageManager()
{
	SAFE_RELEASE(m_sprite);
	m_font->Release();

	for (auto iter : m_imgs)
		SAFE_DELETE(iter.second);
	m_imgs.clear();
}

void cImageManager::Begin(bool isUI)
{
	if (isUI) {
		//OBJECTSPACE를 설정하지 않을 경우 이미지가 윈도우 좌표 기준으로 그려진다.
		m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
	}
	else {
		//OBJECTSPACE를 설정하면 카메라가 움직이더라도 이미지는 윈도우 좌표 기준이 아닌
		//월드 좌표 기준으로 그려진다.
		m_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	}
}

void cImageManager::End()
{
	m_sprite->End();
}

void cImageManager::ReBegin(bool isUI)
{
	End();
	Begin(isUI);
}

void cImageManager::LostDevice()
{
	m_sprite->OnLostDevice();
}

void cImageManager::ResetDevice()
{
	m_sprite->OnResetDevice();
}

void cImageManager::AddTexture(string name, string path, int cnt)
{
	auto find = m_imgs.find(name);
	if (find != m_imgs.end()) {
		DEBUG_LOG("이미 같은 이름의 이미지가 있네유..\n");
		return;
	}
	else if (cnt < 0) {
		DEBUG_LOG("%d는 cnt에 넣을 수 없어유...\n", cnt);
		return;
	}

	cMultiTexture* text = new cMultiTexture;
	text->AddImage(path, cnt);
	m_imgs[name] = text;
}

cTexture* cImageManager::FindTexture(string name, int cnt)
{
	auto find = m_imgs.find(name);
	if (find == m_imgs.end()) {
		for (auto iter : m_imgs)
			DEBUG_LOG("%s\n", iter.first.c_str());
		DEBUG_LOG("찾는 이미지가 없어유..\n");
		return nullptr;
	}
	return find->second->FindImage(cnt);
}

void cImageManager::Render(cTexture* text, VEC2 pos, VEC2 size, float rot, bool isCenter, D3DCOLOR color)
{
	if (text) {
		MATRIX mat, s, r, t;
		D3DXMatrixScaling(&s, size.x, size.y, 1.f);
		D3DXMatrixRotationZ(&r, D3DXToRadian(rot));
		D3DXMatrixTranslation(&t, pos.x, pos.y, 0.f);

		mat = s * r * t;
		m_sprite->SetTransform(&mat);
		if (isCenter)
			m_sprite->Draw(text->m_text, nullptr, &VEC3(text->m_info.Width / 2, text->m_info.Height / 2, 0.f), nullptr, color);
		else
			m_sprite->Draw(text->m_text, nullptr, nullptr, nullptr, color);
	}
	else DEBUG_LOG("텍스쳐가 비었소\n");
}

void cImageManager::CenterRender(cTexture* text, VEC2 pos, VEC2 center, float size, float rot, D3DCOLOR color)
{
	if (text) {
		MATRIX mat, s, r, t;
		D3DXMatrixScaling(&s, size, size, 1.f);
		D3DXMatrixRotationZ(&r, D3DXToRadian(rot));
		D3DXMatrixTranslation(&t, pos.x, pos.y, 0.f);

		mat = s * r * t;

		m_sprite->SetTransform(&mat);
		m_sprite->Draw(text->m_text, nullptr, &VEC3(center.x, center.y, 0.f), nullptr, color);
	}
	else DEBUG_LOG("텍스쳐가 비었소\n");
}

void cImageManager::CropRender(cTexture* text, VEC2 pos, VEC2 size, RECT rt, bool isCenter)
{
	MATRIX mat, s, t;
	D3DXMatrixScaling(&s, size.x, size.y, 1.f);
	D3DXMatrixTranslation(&t, pos.x, pos.y, 0.f);
	mat = s * t;

	m_sprite->SetTransform(&mat);

	if (isCenter) {
		m_sprite->Draw(
			text->m_text, &rt,
			&VEC3(text->m_info.Width / 2, text->m_info.Height / 2, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
	else {
		m_sprite->Draw(
			text->m_text, &rt, nullptr, nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
}

void cImageManager::DrawNum(string text, VEC2 pos, int numD, VEC2 size)
{
	cTexture* nowImg;
	for (size_t i = 0; i < text.size(); ++i) {
		char key[256];
		sprintf(key, "num_%c", text[i]);
		nowImg = FindTexture(key);
		Render(nowImg, VEC2(pos.x + (i * numD), pos.y), size);
	}
}

void cImageManager::DrawFloat(string text, VEC2 pos, int length, int dotD, int numD, VEC2 size)
{
	cTexture* nowImg;
	for (size_t i = 0; i < length; ++i) {
		if (text[i] == '.') {
			nowImg = FindTexture("num_dot");
			Render(nowImg, VEC2(pos.x + (i * dotD), pos.y + 10), size);
		}
		else {
			char key[256];
			sprintf(key, "num_%c", text[i]);
			nowImg = FindTexture(key);
			Render(nowImg, VEC2(pos.x + (i * numD), pos.y), size);
		}
	}
}

void cImageManager::DrawFont(string text, VEC2 pos, D3DCOLOR color)
{
	RECT rt = { pos.x, pos.y, 0, 0 };
	MATRIX mat;
	D3DXMatrixIdentity(&mat);
	m_sprite->SetTransform(&mat);

	m_font->DrawTextA(
		m_sprite,
		text.c_str(),
		-1,
		&rt,
		DT_NOCLIP,
		color
	);
}