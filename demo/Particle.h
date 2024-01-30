#pragma once
#include "Effect.h"

class Particle : public Effect
{
public:

	Particle();
	~Particle();

	void Init();
	void Update();
	void Draw();

	void WantPos(Vec2 pos) { m_pos = pos; }


private:
	Vec2 m_pos;
	Vec2 m_velocity;

	int m_num;
	int a;
};

