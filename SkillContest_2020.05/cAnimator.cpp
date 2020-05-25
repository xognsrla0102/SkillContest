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
			//�����̰� 0���� ũ�� ���� �̹����� ������ �ѱ��
			if (m_delay > 0 && m_currentFrame < m_images.size() - 1)
				m_currentFrame++;
			//�����̰� 0���� �۰� ���� �̹����� 0�� �ƴϸ�
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

