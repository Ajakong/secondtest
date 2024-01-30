#pragma once
#include<iostream>
#include<memory>
#include"Vec2.h"
#include"Rect.h"

class EneShot;

class EneShotEffect
{
public:
	EneShotEffect();
	~EneShotEffect();

	void Init();
	void Update();
	void Draw();

	void WantHitPos(EneShot* shot, const Vec2 pos) { m_shot = shot; m_pos = pos; m_isAppear = true; }

private:
	Vec2 m_pos;

	bool m_isAppear = false;

	int m_radius = 0;

	int m_lineThickNess = 5;

	EneShot* m_shot;

};

