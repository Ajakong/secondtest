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
	void Update();
	void Draw(int screenmove);

	void WantHitPos(Shot* shot, const Vec2& pos, int screenMove);
	
private:
	Vec2 m_pos;

	bool m_isAppear = false;

	int m_radius = 0;
	
	int m_frame;

	int m_lineThickNess = 5;

	int m_screenMove = 0;
	int m_firstScreenMove=0;

	Shot* m_shot;

};

