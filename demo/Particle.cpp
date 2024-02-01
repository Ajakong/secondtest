#include"Dxlib.h"
#include "Particle.h"

Particle::Particle()
{
	for (int i = 0; i < 100; i++)
	{
		m_pos[i].x = 0;
		m_pos[i].y = 1090;
		m_velocity[i].x = 0;
		m_velocity[i].y = -1;
		m_useParticle[i] = false;
	}
	m_handle = LoadGraph("data/effect/particle_v.png");
}

Particle::~Particle()
{
}

void Particle::Init()
{
	
}

void Particle::Update()
{
	for (int i = 0; i < 100; i++)
	{
		if(m_useParticle[i]==true)
		{
			if (m_pos[i].y <= -200)
			{
				m_pos[i].y = 1090;
				m_useParticle[i] = false;
			}
			if (m_pos[i].y == 1090)
			{
				m_pos[i].x = GetRand(2000);
				m_velocity[i].x = GetRand(2000)-m_pos[i].x;
				m_velocity[i].y = -GetRand(1000);
				m_velocity[i].Normalize();
				//m_velocity[i].y -= 1;
			}
			m_pos[i] += m_velocity[i];
		}
		
	}
	m_createFrame++;
}

void Particle::Draw()
{
	for (int i = 0; i < 100; i++)
	{
		if (m_useParticle[i])
		{
			DrawRotaGraph(m_pos[i].x, m_pos[i].y,0.5,0, m_handle,true);
			//DrawBox(m_pos[i].x - 50, m_pos[i].y - 50, m_pos[i].x + 50, m_pos[i].y + 50, 0xffbbff, false);
		}
		if (m_createFrame % 2000 == GetRand(4000))
		{
			m_useParticle[i] = true;
		}
	}
}
