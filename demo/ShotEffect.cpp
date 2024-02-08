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

void ShotEffect::Update()
{
	if (m_isAppear)
	{
		m_frame++;
		m_radius++;
		m_lineThickNess--;

		

		if (m_radius >= 20)
		{
			m_shot->OnDestroy();
		}
	}
}

void ShotEffect::Draw(int screenmove)
{
	if (m_isAppear)
	{
		DrawCircle(m_pos.x-screenmove + m_firstScreenMove , m_pos.y, m_radius, 0xffdddd, false, 2);
	}
}

void ShotEffect::WantHitPos(Shot* shot, const Vec2& pos, int screenMove)
{
	 m_shot = shot;
	 m_pos = pos; 
	 m_isAppear = true;
	 m_firstScreenMove=screenMove;
}
