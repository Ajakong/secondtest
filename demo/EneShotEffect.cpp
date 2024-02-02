#include"Dxlib.h"
#include"EneShot.h"
#include"EneShotEffect.h"

EneShotEffect::EneShotEffect():
	m_pos(0,0)
{

}

EneShotEffect::~EneShotEffect()
{
}

void EneShotEffect::Init()
{
}

void EneShotEffect::Update()
{
	if (m_isAppear)
	{
		m_radius++;
		m_lineThickNess--;
		if (m_radius >= 40)
		{
			m_shot->OnDestroy();
		}
	}
}

void EneShotEffect::Draw()
{
	if (m_isAppear)
	{
		DrawCircle(m_pos.x, m_pos.y, m_radius, 0xff00dd, false, 2);
	}

}
