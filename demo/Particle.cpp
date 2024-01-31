#include"Dxlib.h"
#include "Particle.h"

Particle::Particle()
{
	for (int i = 0; i < 100; i++)
	{
		m_pos[i].x = 0;
		m_pos[i].y = 1090;
		m_velocity[i].x = 0;
		m_velocity[i].y = 0;

	}
}

Particle::~Particle()
{
}

void Particle::Init()
{
}

void Particle::Update()
{

	
}

void Particle::Draw()
{
	for (int i = 0; i < 100; i++)
	{
		m_pos[i].x = GetRand(2000);
		if(m_createFrame%100)
	
		DrawLine(m_pos[i].x, m_pos[i].y, m_pos[i].x - i * 0.42, m_pos[i].y - i * 0.01, 0xffff22);
	}
}
