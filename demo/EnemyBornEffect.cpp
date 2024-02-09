#include "EnemyBornEffect.h"
#include"Dxlib.h"

EnemyBornEffect::EnemyBornEffect()
{
}

EnemyBornEffect::~EnemyBornEffect()
{
}

void EnemyBornEffect::Init()
{
}

void EnemyBornEffect::Update()
{
}

void EnemyBornEffect::Draw(int m_screenMove)
{
	m_exisFrame++;
	for (int h = 0; h < 100; h++)
	{
		for (int w = m_reductionFrame; w < 50-m_reductionFrame; w++)
		{
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - h * 2.5);
			DrawPixel(m_pos.x - w+m_screenMove-m_firstScreenMove, m_pos.y - h, 0xff1100);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	if (m_exisFrame > 30)
	{
		m_reductionFrame++;
	}
	if (m_reductionFrame > 25)
	{
		m_isDestroy = true;
	}
}

void EnemyBornEffect::CreateEffect(Vec2 pos, float offSetX, float offSetY, int screenMove)
{
	m_pos = pos;
	m_offSetX = offSetX;
	m_offSetY = offSetY;
	m_firstScreenMove = screenMove;
	m_isExisFlag = true;
}
