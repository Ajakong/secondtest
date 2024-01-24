#pragma once
#include<iostream>
#include<memory>
#include"Vec2.h"
#include"Rect.h"

class Enemy;

class DieEnemyEffect
{
	DieEnemyEffect();
	~DieEnemyEffect();

	void Init();
	void Update();
	void Draw();

	void OnDie(Enemy* enemy, Vec2 pos) { m_enemy = enemy, m_pos = pos, m_isAppear = true; }

private:
	Vec2 m_pos;

	bool m_isAppear = false;

	int m_radius = 0;

	int m_lineThickNess = 5;

	Enemy* m_enemy;
};

