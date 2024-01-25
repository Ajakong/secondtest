#include"Dxlib.h"
#include"Shot.h"
#include "ShotEffect.h"

ShotEffect::ShotEffect():
	m_pos(0,0),
	m_isAppear(false)
{
	
}

ShotEffect::~ShotEffect()
{
}

void ShotEffect::Init()
{
}

void ShotEffect::Update(int screenmove)
{
	if (m_isAppear)
	{
		m_pos.x -= screenmove;
		m_radius++;
		m_lineThickNess--;
		if (m_radius >= 40)
		{
			m_shot->OnDestroy();
		}
	}


}

void ShotEffect::Draw()
{
	if (m_isAppear)
	{
		DrawCircle(m_pos.x, m_pos.y, m_radius, 0xffdddd, false, 2);
	}

}
