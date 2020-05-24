#include "DXUT.h"
#include "cGameManager.h"

cGameManager::cGameManager()
{
	Init();
}

cGameManager::~cGameManager()
{
	Release();
}

void cGameManager::Init()
{
	SetInst();
}

void cGameManager::Update()
{
}

void cGameManager::Render()
{
}

void cGameManager::Release()
{
}

void cGameManager::SetTimeSpeed(FLOAT Speed)
{
}

void cGameManager::SetInst()
{
	m_life = 3;
	m_startLife = m_life;
	m_score = 0;
	m_power = 0;
	m_level = 1;
	m_exp = 0;
	m_needEXP = 100;

	m_timeSpeed = 1.f;

	m_isShield = FALSE;
	m_isBoom = FALSE;
}
