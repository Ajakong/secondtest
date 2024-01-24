#pragma once

class EnemyBase;

class EnemyToPlayer;

class EnemyManager
{
	EnemyManager();
	virtual ~EnemyManager();

	EnemyBase* m_EnemyBase;
	EnemyToPlayer* m_EnemyToPlayer;
};

