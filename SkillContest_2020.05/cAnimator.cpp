#include "DXUT.h"
#include "cRenderer.h"
#include "cAnimator.h"

cAnimator::cAnimator(cObject* obj, string imageKey, FLOAT delay, BOOL once)
	:cComponent(obj), m_delay(delay), m_defaultDelay(delay), m_once(once)
{
	m_pause = FALSE;
	m_images = IMAGE->FindAnimation(imageKey);
	m_pObj->GetComponent<cRenderer>()->SetImage(m_images[0]);
	m_currentFrame = 1;

	m_timer = new cTimer(
		delay,
		[&]()->void {
			//딜레이가 0보다 크고 다음 이미지가 있으면 넘기기
			if (m_delay > 0 && m_currentFrame < m_images.size() - 1)
				m_currentFrame++;
			//딜레이가 0보다 작고 현재 이미지가 0이 아니면
			else if (m_delay < 0 && m_currentFrame != 0)
				m_currentFrame--;
			else if (m_delay > 0 && m_currentFrame == m_images.size() - 1) {
				if (m_once) m_pause = TRUE;
				else m_currentFrame = 0;
			}
			else {
				if (m_once) m_pause = TRUE;
				else m_currentFrame = m_images.size() - 1;
			}
			m_pObj->GetComponent<cRenderer>()->SetImage(m_images[m_currentFrame]);
		},
		TRUE
	);
}

cAnimator::~cAnimator()
{
}

void cAnimator::Init()
{
}

void cAnimator::Update()
{
	if (!m_pause) m_timer->Update();
}

void cAnimator::Render()
{
}

void cAnimator::Release()
{
	SAFE_DELETE(m_timer);
}

