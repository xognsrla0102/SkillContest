#pragma once

class cBullet;
class cBulletManager : public cObject
{
private:
	vector<cBullet*> m_bullets;
public:
	cBulletManager();
	virtual ~cBulletManager();

	virtual void Update() override;
	virtual void Render() override;
	void Reset();

	vector<cBullet*>& GetBullets() { return m_bullets; }
	
	//»ç¿ë ¿¹
	/*
	
	void cEnemy::Fire(int pattern) {
		switch (pattern) {
			case 0:
				((cBulletManager*)OBJFIND(BULLET))->N_WAY_TAN(5, m_pos, OBJFIND(PLAYER)->GetPos() - m_pos);
				break;
			default:
				break;
		}
	}
	*/


	//ºÎÃ¤²Ã ¼¦
	void N_Way_Tan(int n, VEC2 pos, VEC2 dir, bool isRandShot = false, bool isHoming = false, bool isAccel = false);
	//Á÷»ç°¢Çü ¼¦
	void N_Straight_Tan(int n, VEC2 pos, VEC2 dir, bool isAccel = false);
	//ÅÂ¾ç°è ¼¦
	void N_Tornado_Tan(int n, VEC2 pos, VEC2 dir, bool isLeftDir = false);
	//ÆÄµµ ¼¦
	void N_Wave_Tan(int n, VEC2 pos, VEC2 dir, bool isAccel = false);
};

