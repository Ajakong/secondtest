#pragma once
#include<iostream>
#include<memory>
#include"Vec2.h"
#include"Rect.h"

class Shot;

class ShotEffect
{
public:
	ShotEffect();
	~ShotEffect();

	void Init();
	void Update(int screenmove);
	void Draw();

	void WantHitPos(Shot* shot, const Vec2& pos) { m_shot = shot; m_pos = pos; m_isAppear = true;	}
	
private:
	Vec2 m_pos;

	bool m_isAppear = false;

	int m_radius = 0;

	int m_lineThickNess = 5;

	Shot* m_shot;

};

