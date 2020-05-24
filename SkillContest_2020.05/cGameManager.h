#pragma once
#include "cSingleton.hpp"

struct RankData
{
	INT score;
	string character;
};

class cGameManager : public cSingleton<cGameManager>
{
private:
	INT m_life		= 3;
	INT m_startLife = m_life;
	INT m_score		= 0;
	INT m_power		= 0;
	INT m_level		= 1;
	INT m_exp		= 0;
	INT m_needEXP	= 100;

	FLOAT m_timeSpeed = 1.f;

	BOOL m_isShield	= FALSE;
	BOOL m_isBoom	= FALSE;

	map<string, RankData> m_rank;
public:
	cGameManager();
	virtual ~cGameManager();

	void Init();
	void Update();
	void Render();
	void Release();

	void SetTimeSpeed(FLOAT Speed);
	void SetInst();
public:
	void SetLife(INT Life)
	{
		m_life = Life;
	}

	void SetStartLife(INT Life)
	{
		m_startLife = Life;
	}

	void SetScore(INT Score)
	{
		m_score = Score;
	}

	void SetPower(INT Power)
	{
		m_power = Power;
	}

	FLOAT GetTimeSpeed()
	{
		return m_timeSpeed;
	}

	INT GetLife()
	{
		return m_life;
	}

	INT GetStartLife()
	{
		return m_startLife;
	}

	INT GetScore()
	{
		return m_score;
	}

	void AddLife(INT Life)
	{
		m_life += Life;
	}

	INT GetPower()
	{
		return m_power;
	}

	void AddScore(INT Score)
	{
		m_score += Score;
	}

	void AddPower(INT Power)
	{
		m_power += Power;
	}
};

#define GAME cGameManager::GetInst()