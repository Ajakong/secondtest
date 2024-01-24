#include"Dxlib.h"
#include "Particle.h"

Particle::Particle()
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


}

void Particle::Draw()
{
	DrawPixel(m_pos.x, m_pos.y, 0xffffff);
}
