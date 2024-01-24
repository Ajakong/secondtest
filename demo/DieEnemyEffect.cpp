#include"DxLib.h"
#include "DieEnemyEffect.h"


DieEnemyEffect::~DieEnemyEffect()
{
}

void DieEnemyEffect::Init()
{
}

void DieEnemyEffect::Update()
{
	if (m_isAppear)
	{
		m_radius++;
		m_lineThickNess--;
		if (m_radius >= 40)
		{
			
		}
	}
	
}

void DieEnemyEffect::Draw()
{
	if (m_isAppear)
	{
		DrawCircle(m_pos.x, m_pos.y, m_radius, 0xffdddd, false, 2);
	}
}
