#include"Dxlib.h"
#include "Particle.h"

Particle::Particle():
	m_pos(500,500),
	m_velocity(0,0)
{
}

Particle::~Particle()
{
}

void Particle::Init()
{
}

void Particle::Update()
{
	/*a++;
	m_num = 30*sinf(3.14 * a / 20);*/
}

void Particle::Draw()
{
	for (int i = 0; i < 100; i++)
	{
		m_pos.x = m_num*sinf(i*3.14/50)+m_pos.x;
		m_pos.y = -m_num*cosf(i*3.14/50)+m_pos.y;
		m_pos += m_velocity;
		DrawLine(m_pos.x,m_pos.y,m_pos.x - i * 0.42, m_pos.y - i * 0.01, 0xffff22);
	}
	

}
