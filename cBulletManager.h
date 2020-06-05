#pragma once

class cBullet;
class cBulletManager : public cObject
{
private:
	vector<cBullet*> m_pBullet;
	vector<cBullet*> m_eBullet;
public:
	cBulletManager();
	virtual ~cBulletManager();

	virtual void Update() override;
	virtual void Render() override;
	void Reset();

	vector<cBullet*>& GetPlayerBullets() { return m_pBullet; }
	vector<cBullet*>& GetEnemyBullets()  { return m_eBullet; }

	//ºÎÃ¤²Ã ¼¦
	void N_Way_Tan(const string& bulletName, const string& imageName, int n, int theta, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isRandShot = false, bool isHoming = false, bool isFaccel = false, bool isSaccel = false);
	//Á÷»ç°¢Çü ¼¦
	void N_Straight_Tan(const string& bulletName, const string& imageName, int n, int length, VEC2 pos, VEC2 dir, VEC2 size, float bulletSpd, float atk, bool isFaccel = false, bool isSaccel = false);
};

