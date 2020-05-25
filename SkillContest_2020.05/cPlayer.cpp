#include "DXUT.h"
#include "cPlayer.h"

cPlayer::cPlayer(cObject* obj)
	: cComponent(obj)
{
}

cPlayer::~cPlayer()
{
}

void cPlayer::Init()
{
	OBJECT->SetPlayer(m_pObj);
	m_pObj->SetScale(VEC2(0.4f, 0.4f));

	m_pObj->AddComponent<cAnimation>();
	m_pObj->GetComponent<cAnimation>()->AddAnimator("Idle", "player", 6);
	m_pObj->GetComponent<cAnimation>()->SetCurrentAnimator("Idle");

	m_pObj->AddComponent<cCircleCollider>();
	m_pObj->GetComponent<cCircleCollider>()->SetRad(2);
	m_pObj->GetComponent<cCircleCollider>()->AddListName("EnemyBullet");
	m_pObj->GetComponent<cCircleCollider>()->SetCollFunc([&](cObject* other)->void {
		if (m_isHit == FALSE && other->GetName() == "EnemyBullet")
		{
			m_pObj->GetComponent<cCircleCollider>()->SetEnable(FALSE);
			m_pObj->GetComponent<cRenderer>()->SetEnable(FALSE);

			//cEffect* a = EFFECT->Create("Player_Idle1", m_pObj->GetPos(), VEC2(1.5, 1.5), -10);
			//EFFECT->AlphaSetting(a, 200, -5);
			//EFFECT->SizeSetting(a, VEC2(-0.075, 0.075));
			//a = EFFECT->Create("EnemyDeath1", m_pObj->GetPos(), VEC2(0.5, 0.5), -10);
			//EFFECT->SizeSetting(a, VEC2(0.2, 0.2));
			//EFFECT->AlphaSetting(a, 200, -15);

			GAME->AddLife(-1);
			if (GAME->GetLife() == 0) {
				m_fireDelay = new cTimer(120, [&]()->void {
					m_fireDelay = nullptr;
					SAFE_DELETE(m_fireDelay);
					SCENE->ChangeScene("GameOverScene");
					}
				);
			}
			else
			{
				m_fireDelay = new cTimer(60, [&]()->void {
					m_pObj->SetPos(VEC2(winSizeX / 2, winSizeY / 2));
					//cEffect* a = EFFECT->Create("Player_Idle1", m_pObj->GetPos(), VEC2(3, 3), 1);
					//EFFECT->AlphaSetting(a, 5, 3);
					//EFFECT->SizeSetting(a, VEC2(-0.075, -0.075));
					m_fireDelay = nullptr;
					SAFE_DELETE(m_fireDelay);
					}
				);
			}
		}
	});
	
	//m_bullet = IMAGE->FindTexture("PlayerBullet1"); 
}

void cPlayer::Update() 
{
	DEBUG_LOG("x : %.2f, y : %.2f\n", m_pObj->GetPos().x, m_pObj->GetPos().y);

	if (m_isHit == FALSE) {
		if (KEYPRESS(VK_LSHIFT)) {
			m_pSpd = 250.f;
		}
		else {
			m_pSpd = 500.f;
		}

		if (KEYPRESS(VK_LEFT)) {
			if (m_pObj->GetPos().x > 0) m_pObj->Translate(VEC2(-m_pSpd, 0) * D_TIME);
			else m_pObj->SetPos(VEC2(0, m_pObj->GetPos().y));
		}
		if (KEYPRESS(VK_RIGHT)) {
			if (m_pObj->GetPos().x < winSizeX) m_pObj->Translate(VEC2(m_pSpd, 0) * D_TIME);
			else m_pObj->SetPos(VEC2(winSizeX, m_pObj->GetPos().y));
		}
		if (KEYPRESS(VK_UP)) {
			if (m_pObj->GetPos().y > 0) m_pObj->Translate(VEC2(0, -m_pSpd) * D_TIME);
			else m_pObj->SetPos(VEC2(m_pObj->GetPos().x, 0));
		}
		if (KEYPRESS(VK_DOWN)) { 
			if (m_pObj->GetPos().y < winSizeY) m_pObj->Translate(VEC2(0, m_pSpd) * D_TIME);
			else m_pObj->SetPos(VEC2(m_pObj->GetPos().x, winSizeY));
		}
		if (KEYPRESS(VK_SPACE)) {
			Fire();
		}
	}
	else {
		OBJECT->With(OBJ_Tag::BULLET, [&](cObject* obj)->void {
			obj->Destroy();
		});
	}

	if (m_fireDelay) m_fireDelay->Update();
}

void cPlayer::Render()
{
}

void cPlayer::Release()
{
	if (m_fireDelay) {
		SAFE_DELETE(m_fireDelay);
	}
}

cObject* cPlayer::AddBullet(VEC2 pos, FLOAT dir, INT dmg, cTexture* text)
{
	return nullptr;
}

cObject* cPlayer::AddBullet(VEC2 pos, FLOAT dir, INT dmg, cTexture* text, cObject* target)
{
	return nullptr;
}

void cPlayer::Fire()
{
}


