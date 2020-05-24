#include "DXUT.h"
#include "cAnimator.h"
#include "cAnimation.h"

cAnimation::cAnimation(cObject* obj) : cComponent(obj)
{
}

cAnimation::~cAnimation()
{
}

void cAnimation::Init()
{
	m_playSpeed = GAME->GetTimeSpeed();
}

void cAnimation::Update()
{
	if (m_currentAnimator)
		m_currentAnimator->Update();
}

void cAnimation::Render()
{
}

void cAnimation::Release()
{
	for (auto iter : m_animators) {
		iter.second->Release();
		SAFE_DELETE(iter.second);
	}
	m_animators.clear();
}


string cAnimation::GetCurrentAnimatorKey()
{
	return m_currentAnimator->m_key;
}

FLOAT cAnimation::GetPlaySpeed()
{
	return m_playSpeed;
}

void cAnimation::SetPlaySpeed(FLOAT speed)
{
	m_playSpeed = speed * GAME->GetTimeSpeed();
	if (!m_currentAnimator) return;
	m_currentAnimator->m_delay = m_currentAnimator->m_defaultDelay / m_playSpeed;
	m_currentAnimator->m_timer->m_time = abs(m_currentAnimator->m_delay);
}

INT cAnimation::GetCurrentFrame()
{
	if (!m_currentAnimator) return 0;
	return m_currentAnimator->m_currentFrame;
}

void cAnimation::SetCurrentFrame(INT frame)
{
	if (!m_currentAnimator) return;
	if (frame > m_currentAnimator->m_images.size() - 1) frame = m_currentAnimator->m_images.size() - 1;
	m_currentAnimator->m_currentFrame = frame;
}

BOOL cAnimation::GetPaused()
{
	return m_currentAnimator->m_pause;
}

void cAnimation::SetPaused(BOOL pause)
{
	m_currentAnimator->m_pause = pause;
}

cAnimator* cAnimation::FindAnimator(string key)
{
	auto find = m_animators.find(key);
	if (find == m_animators.end()) return nullptr;
	return find->second;
}

cAnimator* cAnimation::AddAnimator(string key, string imageKey, FLOAT delay, BOOL once)
{
	if (FindAnimator(key)) return nullptr;
	cAnimator* animator = new cAnimator(m_pObj, imageKey, delay, once);
	animator->m_key = key;
	m_animators[key] = animator;
	return animator;
}

void cAnimation::SetCurrentAnimator(string key)
{
	if (!FindAnimator(key)) DEBUG_LOG("%s 애니메이터가 없습니다.\n", key.c_str());
	m_currentAnimator = FindAnimator(key);
	m_currentAnimator->m_timer->m_curTime = 0;
	m_currentAnimator->m_pause = FALSE;
	SetPlaySpeed(m_playSpeed);
}
