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
	
	//��� ��
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


	//��ä�� ��
	void N_Way_Tan(int n, VEC2 pos, VEC2 dir, bool isRandShot = false, bool isHoming = false, bool isAccel = false);
	//���簢�� ��
	void N_Straight_Tan(int n, VEC2 pos, VEC2 dir, bool isAccel = false);
	//�¾�� ��
	void N_Tornado_Tan(int n, VEC2 pos, VEC2 dir, bool isLeftDir = false);
	//�ĵ� ��
	void N_Wave_Tan(int n, VEC2 pos, VEC2 dir, bool isAccel = false);
};

