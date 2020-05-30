#pragma once
#include "cObject.h"

class cEnemy;
class cEnemyManager : public cObject
{
private:
	vector<cEnemy*> m_meteor;
public:
	cEnemyManager();
	~cEnemyManager();

	virtual void Update() override;
	virtual void Render() override;
	void Release();

	vector<cEnemy*>& GetMeteor() { return m_meteor; }
};

