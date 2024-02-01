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

private:
	Vec2 m_pos[100];
	Vec2 m_velocity[100];

	int m_num;
	int m_createFrame=0;
	int m_handle = 0;


	bool m_useParticle[100];
};

