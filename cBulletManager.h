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

	vector<cBullet*>& GetBullets() { return m_bullets; }

	void N_Way_Tan(int n, VEC2 pos, bool isRandShot = false, bool isHoming = false, bool isAccel = false);
	void N_Straight_Tan(int n, VEC2 pos, bool isAccel = false);
	void N_Tornado_Tan(int n, VEC2 pos, bool isLeftDir = false);
};

